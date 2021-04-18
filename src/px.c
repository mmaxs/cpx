
// some quirks of format specifiers on Windows:
#if defined(__MINGW32__) || defined(__MINGW64__)
    // https://sourceforge.net/p/mingw-w64/wiki2/gnu printf/
    // https://sourceforge.net/p/mingw-w64/wiki2/printf and scanf family/
#   define __USE_MINGW_ANSI_STDIO 1
#endif

#ifdef PX_DEBUG
#   undef NDEBUG
#else
#   define NDEBUG
#endif

#include <stddef.h>   // NULL size_t
#include <string.h>   // memset
#include <stdlib.h>   // exit
#include <assert.h>
#include <stdio.h>    // stderr fprintf fflush FILE
#include <stdarg.h>
#include <ctype.h>    // isgraph
#include <limits.h>   // CHAR_BIT
#include <stdint.h>   // SIZE_MAX

// some quirks for the multithreading support header:
#ifdef PX_NO_MULTITHREADING
#   define px_Thread_local
#else
#   define px_Thread_local _Thread_local
#   ifdef __STDC_NO_THREADS__
#     include <pthread.h>
#     define px_thrd_current pthread_self
#   elif defined(__MINGW32__) || defined(__MINGW64__)
      // Mingw-w64 doesn't define the '__STDC_NO_THREADS__' guard macro nor provide the <threads.h> standard header
#     include <pthread.h>
#     define px_thrd_current pthread_self
#   else
#     include <threads.h>
#     define px_thrd_current thrd_current
#   endif
#endif


#include "px.h"


// the forward declaration for a debug log function:
#ifdef PX_DEBUG
static int px_log(const char *const restrict, ...);
#else
#   define px_log(...) ((int)0)
#   pragma GCC diagnostic ignored "-Wunused-value"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#endif


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
    This section implements a fairly standard functions to manipulate
    a stack structure with a fixed-length array storage backend.
*/

typedef _PX_JMPBUF_TYPE* ctx_t;  // the stack element type

#define CTX_STACK_SIZE  (PX_NESTING_CATCH_LIMIT)         //
#define ctx_stack_end   (ctx_stack + CTX_STACK_SIZE)     // the stack exhaustion sentinel
px_Thread_local static ctx_t ctx_stack[CTX_STACK_SIZE];  //
px_Thread_local static ctx_t *ctx_stack_top = NULL;      // the top of stack pointer; NULL if stack is empty


static _Bool ctx_stack_push(const ctx_t ctx)
{
  // spot the new top of stack:
  ctx_t *const top = (ctx_stack_top ? (ctx_stack_top + 1) : ctx_stack);
  
  // return a failure on stack exhaustion:
  if (! (top < ctx_stack_end)) return 0;
  
  // push in the new element:
  *top = ctx;
  ctx_stack_top = top;
  
  return 1;
}

static _Bool ctx_stack_pop(ctx_t *const ctx_ref)
{
  // return a failure on stack underrun:
  if (! ctx_stack_top) return 0;
  
  // pop out the top of stack element:
  if (ctx_ref) *ctx_ref = *ctx_stack_top;
  ctx_stack_top = (ctx_stack_top == ctx_stack ? NULL : (ctx_stack_top - 1));
  
  return 1;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
    The following functions actually are interfaces to the stack manipulation
    functions introduced above, and intended to be used in user interface
    macros (PX_CATCH_AT, PX_THROW, PX_CATCH_EXPECTED). They are designed to be
    either the event handlers (_onXXX suffix), or the commands
    (_commandXXX suffix) invoked when the environment (context) should be
    saved/changed with setjmp()/longjmp(), or tested for availability.
*/

/*! */
_PX_JMPBUF_TYPE* _px_ctx_onBegin(_PX_JMPBUF_TYPE *const ctx)
{
  assert (ctx);
  px_log("%s: ctx=%p ctx_stack_top=%p *ctx_stack_top=%p\n", __func__, ctx, ctx_stack_top, (ctx_stack_top ? *ctx_stack_top : NULL));

  // don't store the very same ctx in a row (perhaps being called from a tail recursion optimized function):
  if (ctx_stack_top && (*ctx_stack_top == ctx))
  {
    px_log("%s: | skip ctx_stack_push on the same ctx\n", __func__);
    return ctx;
  };

  // try to store the new ctx:
  _Bool ctx_stack_push_ret = ctx_stack_push(ctx);
  px_log("%s: | ctx_stack_push %s, ctx_stack_top=%p\n", __func__, (ctx_stack_push_ret ? "succeeded" : "failed"), ctx_stack_top);
  
  // on failure, return NULL -- this should be a hint to not calling setjump():
  return (ctx_stack_push_ret ? ctx : NULL);
}

/* Always succeeds. */
_PX_JMPBUF_TYPE* _px_ctx_onEnd(_PX_JMPBUF_TYPE *const ctx)
{
  assert (ctx);
  px_log("%s: ctx=%p ctx_stack_top=%p *ctx_stack_top=%p\n", __func__, ctx, ctx_stack_top, (ctx_stack_top ? *ctx_stack_top : NULL));

  if (ctx_stack_top && (*ctx_stack_top == ctx))
  {
    _Bool ctx_stack_pop_ret = ctx_stack_pop(NULL);
    px_log("%s: | ctx_stack_pop %s, ctx_stack_top=%p\n", __func__, (ctx_stack_pop_ret ? "succeeded" : "failed"), ctx_stack_top);
  }
  else
    px_log("%s: | skip ctx_stack_pop on stack underrun or ctx mismatched\n", __func__);

  return ctx;
}

/* Basically it's a dummy function for debugging purposes. */
_PX_JMPBUF_TYPE* _px_ctx_onLongjmp(_PX_JMPBUF_TYPE *const ctx)
{
  assert (ctx);
  assert (ctx_stack_top);
  assert (*ctx_stack_top == ctx);
  return ctx;
}

_PX_JMPBUF_TYPE* _px_ctx_getLast(void)  { return (ctx_stack_top ? *ctx_stack_top : NULL); }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
*/

px_Thread_local static PX_OBJ_TYPEDEF px_obj;
px_Thread_local static PX_OBJ_TYPEDEF* px = NULL;
px_Thread_local static const char* px_srcline = NULL;
px_Thread_local static const char* px_srcfunc = NULL;


PX_OBJ_TYPEDEF _px_obj_get(void)  { return (px ? *px : px_obj); }

PX_OBJ_TYPEDEF _px_obj_set(PX_OBJ_TYPEDEF px_obj0)
{
  PX_OBJ_TYPEDEF px_obj1 = _px_obj_get();  // use the getter, not simply the px_obj
  px_obj = px_obj0;
  
  px = NULL;
  
  return px_obj1;
}


PX_OBJ_TYPEDEF* _px_get(void)  { return (px ? px : &px_obj); }

PX_OBJ_TYPEDEF* _px_set(PX_OBJ_TYPEDEF *const px0)
{
  PX_OBJ_TYPEDEF *const px1 = _px_get();  // use the getter, not simply the px
  px = px0;

  if (! px)  memset(&px_obj, 0, sizeof(px_obj));

  return px1;
}


const char* _px_srcline_get(void)  { return (px_srcline ? px_srcline : ""); }

const char* _px_srcline_set(const char *const px_srcline0)
{
  const char *const px_srcline1 = px_srcline;
  px_srcline = px_srcline0;
  return px_srcline1;
}


const char* _px_srcfunc_get(void)  { return (px_srcfunc ? px_srcfunc : ""); }

const char* _px_srcfunc_set(const char *const px_srcfunc0)
{
  const char *const px_srcfunc1 = px_srcfunc;
  px_srcfunc = px_srcfunc0;
  return px_srcfunc1;
}


void _px_clear(void)
{
  memset(&px_obj, 0, sizeof(px_obj));
  px = NULL;
  px_srcline = NULL;
  px_srcfunc = NULL;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
*/

typedef void (*px_terminate_func_t)(void);                            // the terminate function signature
px_Thread_local static px_terminate_func_t px_terminate_func = NULL;  //
static void px_default_terminate_func(void);                          // the forward declaration of the default terminate function

/*! The terminate function getter and setter. */
px_terminate_func_t _px_terminate_func_get(void)  { return (px_terminate_func ? px_terminate_func : px_default_terminate_func); }

px_terminate_func_t _px_terminate_func_set(const px_terminate_func_t px_terminate_func0)
{
  const px_terminate_func_t px_terminate_func1 = px_terminate_func;
  px_terminate_func = px_terminate_func0;
  return px_terminate_func1;
}


/*! Helper function for hex dumping the contents of the storage of an arbitrary object. */
int _px_dump(FILE *const restrict stream, const char *const restrict obj, const size_t obj_size)
#define _px_dump__chunk_size 16  // the number of chars to be dumped per a row
#define _px_dump__fprintf(...)\
    do {\
      ret0 = fprintf(__VA_ARGS__);\
      ret = ret0 + (ret0 < 0 ? 0 : ret);\
      if (ret0 < 0)  goto _px_dump__exit;\
    } while (0)
#define _px_dump__char_hexs ((int)(CHAR_BIT/4))                     // hex digits required for printing a char value
#define _px_dump__size_t_hexs ((sizeof(size_t)*CHAR_BIT/4))         // hex digits required for printing the full range of size_t values
#define _px_dump__mask_1_2 (SIZE_MAX << sizeof(size_t)*CHAR_BIT/2)  // high one-half
#define _px_dump__mask_3_4 (SIZE_MAX << sizeof(size_t)*CHAR_BIT/4)  // high three-quarters
{
  assert (obj);

  // define fprintf's return value and the cumulative number of characters printed:
  int ret0 = 0, ret = 0;
  // define the obj index and the chunk character index:
  size_t i = 0, j = 0;
  // the chunk of characters to be dumped (their graphical representation):
  char chunk[_px_dump__chunk_size + 1] = { [_px_dump__chunk_size] = 0 };

  // calculate the minimum sufficient width for printing offset values:
  const int offset_hexs = _px_dump__size_t_hexs / (obj_size & _px_dump__mask_1_2 ? 1 : (obj_size & _px_dump__mask_3_4 ? 2 : 4));
  
  // walk through the obj data:
  for (j = i = 0; i < obj_size; j = ++i % _px_dump__chunk_size)
  {
    // print out the offset value at begin of each chunk:
    if (j == 0)  _px_dump__fprintf(stream, "%.*zx:", offset_hexs, i);

    // print out the current character of the data in hex:
    _px_dump__fprintf(stream, " %.*hhx", _px_dump__char_hexs, obj[i]);

    // collect graphical representations of the dumped characters:
    chunk[j] = (isgraph(obj[i]) ? obj[i] : '.');

    // print out the graphical representation of the chunk dump at its end:
    if (j == (_px_dump__chunk_size - 1))  _px_dump__fprintf(stream, "  %s\n", chunk);
  };
  // if obj_size is not a multiple of _px_dump__chunk_size, print out the missed end stuff;
  // (j is already of one-past-the-end of the actual chunk data):
  if (j != 0)
  {
    chunk[j] = 0;
    _px_dump__fprintf(stream, "%*s  %s\n", (int)((1 + _px_dump__char_hexs)*(_px_dump__chunk_size - j)), "", chunk);
  };
  
_px_dump__exit:
  return ret;
}


/*! Default terminate function called when an exception that cannot be
    caught due to missed CATCH_AT() directive somewhere up in the program call
    stack is thrown. Prints out a nice farewell message and terminates the
    program with `exit(PX_UNCAUGHT_EXCEPTION_EXIT_CODE)`. */
static void px_default_terminate_func(void)
{ 
  fprintf(stderr, "\nUncaught exception from <%s(),%s>.\n", _px_srcfunc_get(), _px_srcline_get());
  fprintf(stderr, "Exception object (%p) dump:\n", (void*)_px_get());
  _px_dump(stderr, (char*)_px_get(), sizeof(PX_OBJ_TYPEDEF));
  fprintf(stderr, "Program terminated with return code %i.\n", PX_UNCAUGHT_EXCEPTION_EXIT_CODE);
  fflush(stderr);

  exit(PX_UNCAUGHT_EXCEPTION_EXIT_CODE);
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
    Debug/log supporting functions.
*/

#ifdef PX_DEBUG

__attribute__(( format(gnu_printf, 1, 2) ))
static int px_log(const char *const restrict format, ...)
{
#ifdef PX_NO_MULTITHREADING
#else
  fprintf(stderr, "[%jX]", px_thrd_current());
#endif

  va_list ap;
  va_start(ap, format);
  int ret = vfprintf(stderr, format, ap);
  va_end(ap);

  fflush(stderr);  // on Mingw-w64, stderr is buffered by default
  return ret;
}

#endif

