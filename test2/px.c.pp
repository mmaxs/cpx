# 1 "px.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "px.c"

# 1 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/9.3.0/include/stddef.h" 1 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/stddef.h" 1 3 4






# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 1 3 4
# 10 "C:/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 1 3 4
# 10 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 1 3 4
# 10 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 1 3 4
# 98 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3 4
             
# 107 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_mac.h" 3 4
             
# 11 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw_secapi.h" 1 3 4
# 12 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 284 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 1 3 4
# 9 "C:/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 1 3 4
# 609 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/sdks/_mingw_ddk.h" 1 3 4
# 610 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 10 "C:/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 2 3 4




#pragma pack(push,_CRT_PACKING)
# 24 "C:/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3 4
  
# 24 "C:/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3 4
 typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 103 "C:/msys64/mingw64/x86_64-w64-mingw32/include/vadefs.h" 3 4
#pragma pack(pop)
# 285 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 2 3 4
# 580 "C:/msys64/mingw64/x86_64-w64-mingw32/include/_mingw.h" 3 4
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{
  __asm__ __volatile__("int {$}3":);
}




const char *__mingw_get_crt_info (void);
# 11 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 2 3 4




#pragma pack(push,_CRT_PACKING)
# 40 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
__extension__ typedef unsigned long long size_t;
# 50 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 67 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
__extension__ typedef long long intptr_t;
# 80 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
__extension__ typedef unsigned long long uintptr_t;
# 93 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
__extension__ typedef long long ptrdiff_t;
# 103 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 143 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
typedef __time64_t time_t;
# 435 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {





  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;

} threadlocinfo;
# 506 "C:/msys64/mingw64/x86_64-w64-mingw32/include/corecrt.h" 3 4
#pragma pack(pop)
# 11 "C:/msys64/mingw64/x86_64-w64-mingw32/include/crtdefs.h" 2 3 4
# 8 "C:/msys64/mingw64/x86_64-w64-mingw32/include/stddef.h" 2 3 4
# 18 "C:/msys64/mingw64/x86_64-w64-mingw32/include/stddef.h" 3 4
  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);


  __attribute__ ((__dllimport__)) extern unsigned long __attribute__((__cdecl__)) __threadid(void);

  __attribute__ ((__dllimport__)) extern uintptr_t __attribute__((__cdecl__)) __threadhandle(void);
# 424 "C:/msys64/mingw64/x86_64-w64-mingw32/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
# 2 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/9.3.0/include/stddef.h" 2 3 4
# 3 "px.c" 2
# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/assert.h" 1 3
# 26 "C:/msys64/mingw64/x86_64-w64-mingw32/include/assert.h" 3
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) exit(int _Code) __attribute__ ((__noreturn__));
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _exit(int _Code) __attribute__ ((__noreturn__));



  void __attribute__((__cdecl__)) _Exit(int) __attribute__ ((__noreturn__));






       

  void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) abort(void);
       



__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wassert(const wchar_t *_Message,const wchar_t *_File,unsigned _Line);
__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _assert (const char *_Message, const char *_File, unsigned _Line);
# 4 "px.c" 2
# 1 "px.h" 1




# 1 "C:/msys64/mingw64/x86_64-w64-mingw32/include/setjmp.h" 1 3
# 11 "C:/msys64/mingw64/x86_64-w64-mingw32/include/setjmp.h" 3
#pragma pack(push,_CRT_PACKING)
# 112 "C:/msys64/mingw64/x86_64-w64-mingw32/include/setjmp.h" 3
  typedef __attribute__ ((__aligned__ (16))) struct _SETJMP_FLOAT128 {
    __extension__ unsigned long long Part[2];
  } SETJMP_FLOAT128;


  typedef SETJMP_FLOAT128 _JBTYPE;

  typedef struct _JUMP_BUFFER {
    __extension__ unsigned long long Frame;
    __extension__ unsigned long long Rbx;
    __extension__ unsigned long long Rsp;
    __extension__ unsigned long long Rbp;
    __extension__ unsigned long long Rsi;
    __extension__ unsigned long long Rdi;
    __extension__ unsigned long long R12;
    __extension__ unsigned long long R13;
    __extension__ unsigned long long R14;
    __extension__ unsigned long long R15;
    __extension__ unsigned long long Rip;
    __extension__ unsigned long long Spare;
    SETJMP_FLOAT128 Xmm6;
    SETJMP_FLOAT128 Xmm7;
    SETJMP_FLOAT128 Xmm8;
    SETJMP_FLOAT128 Xmm9;
    SETJMP_FLOAT128 Xmm10;
    SETJMP_FLOAT128 Xmm11;
    SETJMP_FLOAT128 Xmm12;
    SETJMP_FLOAT128 Xmm13;
    SETJMP_FLOAT128 Xmm14;
    SETJMP_FLOAT128 Xmm15;
  } _JUMP_BUFFER;
# 199 "C:/msys64/mingw64/x86_64-w64-mingw32/include/setjmp.h" 3
  typedef _JBTYPE jmp_buf[16];



__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) __attribute__ ((__nothrow__)) void __attribute__((__cdecl__)) longjmp(jmp_buf _Buf,int _Value);

void * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mingw_getsp (void);

       
# 242 "C:/msys64/mingw64/x86_64-w64-mingw32/include/setjmp.h" 3
  int __attribute__((__cdecl__)) __attribute__ ((__nothrow__,__returns_twice__)) _setjmp(jmp_buf _Buf, void *_Ctx);
  int __attribute__((__cdecl__)) __attribute__ ((__nothrow__,__returns_twice__)) _setjmp3(jmp_buf _Buf, void *_Ctx);
# 270 "C:/msys64/mingw64/x86_64-w64-mingw32/include/setjmp.h" 3
       





#pragma pack(pop)
# 6 "px.h" 2
# 25 "px.h"

# 25 "px.h"
typedef jmp_buf _px_ctx_t;
# 44 "px.h"
_Bool _px_ctx_onBegin(_px_ctx_t*);

void _px_ctx_onJump(_px_ctx_t*);

void _px_ctx_onEnd(_px_ctx_t*);
# 5 "px.c" 2


typedef _px_ctx_t* ctxref_t;



static ctxref_t ctxref_stack[100];

static ctxref_t *const ctxref_stack_end = ctxref_stack + 100;

static ctxref_t *ctxref_stack_top = 
# 15 "px.c" 3 4
                                   ((void *)0)
# 15 "px.c"
                                       ;



static _Bool ctxref_push(ctxref_t ctxref)
{
  ctxref_t *const top = ctxref_stack_top ? (ctxref_stack_top + 1) : ctxref_stack;

  if (! (top < ctxref_stack_end)) return 0;

  *top = ctxref;
  ctxref_stack_top = top;

  return 1;
}

static _Bool ctxref_stack_pop(ctxref_t *ctxref_)
{
  if (! ctxref_stack_top) return 0;

  if (ctxref_) *ctxref_ = *ctxref_stack_top;
  ctxref_stack_top = ctxref_stack_top == ctxref_stack ? 
# 36 "px.c" 3 4
                                                       ((void *)0) 
# 36 "px.c"
                                                            : (ctxref_stack_top - 1);

  return 1;
}






static ctxref_t active_ctx = 
# 46 "px.c" 3 4
                            ((void *)0)
# 46 "px.c"
                                ;


_Bool _px_ctx_onBegin(_px_ctx_t *ctx_ptr) { return ctxref_push(ctx_ptr); }

void _px_ctx_onJump(_px_ctx_t *ctx_ptr)
{
  
# 53 "px.c" 3
 (void) ((!!(
# 53 "px.c"
 ctxref_stack_top && (*ctxref_stack_top == ctx_ptr)
# 53 "px.c" 3
 )) || (_assert(
# 53 "px.c"
 "ctxref_stack_top && (*ctxref_stack_top == ctx_ptr)"
# 53 "px.c" 3
 ,"px.c",53),0))
# 53 "px.c"
                                                           ;
  active_ctx = ctx_ptr;
}

void _px_ctx_onEnd(_px_ctx_t *ctx_ptr)
{





  if (ctxref_stack_top && (*ctxref_stack_top == ctx_ptr)) ctxref_stack_pop(
# 64 "px.c" 3 4
                                                                           ((void *)0)
# 64 "px.c"
                                                                               );
}
