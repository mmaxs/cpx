
#ifndef _PX__H
#define _PX__H 1

#include <setjmp.h>
#include <stdio.h>  // FILE

#include "px.conf.h"


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*
    Default values for customizable properties,
    if they are not provided by the user in "px.conf.h".
*/

#if (PX_NESTING_CATCH_LIMIT) > 0
// macro PX_NESTING_CATCH_LIMIT is properly defined by the user
#else
// macro PX_NESTING_CATCH_LIMIT is not defined (i.e. 0) or defined by the user as zero or negative
#   define PX_NESTING_CATCH_LIMIT 100
#endif

#ifdef PX_OBJ_TYPEDEF
//! Note: if it is to be a non-scalar type, it should be provided with a name declared with typedef.
#else
#   define PX_OBJ_TYPEDEF int
#endif

#ifndef PX_UNCAUGHT_EXCEPTION_EXIT_CODE
#   define PX_UNCAUGHT_EXCEPTION_EXIT_CODE 11
#endif


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*
    Some tune to platform features.
*/
/*! Define _DEFAULT_SOURCE or _GNU_SOURCE macro to use the "default" set of features of the target platform
    (see feature_test_macros(7), <features.h>). */
#ifdef _POSIX_C_SOURCE
#   define _PX_JMPBUF_TYPE            sigjmp_buf
#   define _PX_SETJMP_FUNC(_JMPBUF_)  sigsetjmp(_JMPBUF_, 1)
#   define _PX_LONGJMP_FUNC           siglongjmp
#else
#   define _PX_JMPBUF_TYPE   jmp_buf
#   define _PX_SETJMP_FUNC   setjmp
#   define _PX_LONGJMP_FUNC  longjmp
#endif


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
    Declarations of visible functions. These are functions that are used by
    user interface macros, or functions that can be used directly in client
    code.
*/

/*! Functions for handling the environment for setjmp()/longjmp().
    Used by user interface macros. */
_PX_JMPBUF_TYPE* _px_ctx_onBegin(_PX_JMPBUF_TYPE *const);
_PX_JMPBUF_TYPE* _px_ctx_onEnd(_PX_JMPBUF_TYPE *const);
_PX_JMPBUF_TYPE* _px_ctx_onLongjmp(_PX_JMPBUF_TYPE *const);
_PX_JMPBUF_TYPE* _px_ctx_getLast(void);

/*! Functions for handling the exception object to be thrown and its source location info.
    Used by user interface macros. */
PX_OBJ_TYPEDEF _px_obj_get(void);
PX_OBJ_TYPEDEF _px_obj_set(PX_OBJ_TYPEDEF);
PX_OBJ_TYPEDEF* _px_get(void);
PX_OBJ_TYPEDEF* _px_set(PX_OBJ_TYPEDEF *const);
const char* _px_srcline_get(void);
const char* _px_srcline_set(const char *const);
const char* _px_srcfunc_get(void);
const char* _px_srcfunc_set(const char *const);
void _px_clear(void);

/*! These functions can be used to set a user-defined terminate function invoked
    when an uncaught exception occurs, or to get the default / last set one.
    Use them directly if necessary. */
void (*_px_terminate_func_get(void))(void);
void (*_px_terminate_func_set( void (*const)(void) ))(void);

/*! Helper function for hex dumping the contents of the storage of an arbitrary object.
    Might be useful in client code. */
int _px_dump(FILE *const restrict, const char *const restrict, const size_t);


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
    Auxiliary macros.
*/

#define __TO_STRING_LITERAL_VERBATIM(...) #__VA_ARGS__
#define __TO_STRING_LITERAL_EXPANDED(...) __TO_STRING_LITERAL_VERBATIM(__VA_ARGS__)

#define __CONCAT_VERBATIM(_LHS_, _RHS_) _LHS_##_RHS_
#define __CONCAT_EXPANDED(_LHS_, _RHS_) __CONCAT_VERBATIM(_LHS_, _RHS_)

#define __SOURCE_FILE_LINE __FILE__ ":" __TO_STRING_LITERAL_EXPANDED(__LINE__)
#define __NAME_HOC_LOCO(_PREFIX_) __CONCAT_EXPANDED(_PREFIX_, __LINE__)


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*!
    User interface macros.
*/

/*! Start a protected area extending to the end of the current scope (a 'try' block)
    with catch handlers arranged at _LABEL_ (a 'catch' blocks). */
#define PX_CATCH_AT(_LABEL_)\
  _PX_JMPBUF_TYPE __NAME_HOC_LOCO(_px_ctx_obj) __attribute__(( cleanup(_px_ctx_onEnd) ));\
  if ( _px_ctx_onBegin(&__NAME_HOC_LOCO(_px_ctx_obj)) )\
  {\
    if ( _PX_SETJMP_FUNC(__NAME_HOC_LOCO(_px_ctx_obj)) )\
    {\
      _px_ctx_onLongjmp(&__NAME_HOC_LOCO(_px_ctx_obj));\
      goto _LABEL_;\
    };\
  };


/*! Test whether an exception, if being thrown, will be caught somewhere. */
#define PX_CATCH_EXPECTED()\
  ((_Bool)__px_ctx_getLast())


/*! Throw the given exception _PX_.
    _PX_ can be either an immediate exception value,
    or predefined exception object with static storage duration, or the pointer to it.
    Passing a NULL pointer is equivalent to zero-filled value of exception object. */
#define PX_THROW(_PX_)\
  do {\
    _Generic((_PX_), PX_OBJ_TYPEDEF: _px_obj_set, PX_OBJ_TYPEDEF*: _px_set)((_PX_));\
    _px_srcline_set(__SOURCE_FILE_LINE);\
    _px_srcfunc_set(__func__);\
    if (_px_ctx_getLast())\
    {\
      _PX_LONGJMP_FUNC(*_px_ctx_getLast(), 1);\
    }\
    else\
    {\
      _px_terminate_func_get()();\
    };\
  } while (0)


/*! Set the exception object _PX_ as with PX_THROW, and go to _LABEL_. */
#define PX_THROW_TO(_LABEL_, _PX_)\
  do {\
    _Generic((_PX_), PX_OBJ_TYPEDEF: _px_obj_set, PX_OBJ_TYPEDEF*: _px_set)((_PX_));\
    _px_srcline_set(__SOURCE_FILE_LINE);\
    _px_srcfunc_set(__func__);\
    goto _LABEL_;\
  } while (0)


/*! Re-throw the last exception object being set with PX_THROW/PX_THROW_TO. */
#define PX_RETHROW()\
  if (_px_ctx_getLast())\
  {\
    _PX_LONGJMP_FUNC(*_px_ctx_getLast(), 1);\
  }\
  else\
  {\
    _px_terminate_func_get()();\
  }


/*! Get the pointer to the last thrown exception object provided with PX_THROW/PX_THROW_TO.
    Unless to be directly specified with PX_THROW/PX_THROW_TO, the pointer refers to the
    internal thread local storage with a copy of the provided exception object. */
#define PX()\
  _px_get()


/*! Get the name of the source file and the line number within it where the PX_THROW/PX_THROW_TO was last invoked.
    A static string literal (const char*) in form of "FileName:LineNumber" is returned. */
#define PX_SRCLINE()\
  _px_srcline_get()


/*! Get the name of the function where the PX_THROW/PX_THROW_TO was last invoked.
    The standard predefined string literal `static const char __func__[]` is returned. */
#define PX_SRCFUNC()\
  _px_srcfunc_get()


/*! Clear the last thrown exception and its source location info.
    PX macro will then be returning a pointer to a zero-filled internal storage of exception object,
    and PX_SRCLINE and PX_SRCFUNC macros -- empty strings. */
#define PX_CLEAR()\
  _px_clear()



#endif

