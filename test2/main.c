
#include <stdio.h>
#include <assert.h>
#include "px.h"


jmp_buf jbA, jbB, jbC, jbD;

void cfA(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }
void cfB(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }
void cfC(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }
void cfD(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }


void B(void);

void A(void)
{
  fprintf(stderr, "%s(): entering\n", __func__);

  __attribute__(( cleanup(cfC) ))    // выполняется
  int c = 0;

  if (setjmp(jbA) == 0)
  {
    __attribute__(( cleanup(cfA) ))  // не выполняется
    int a = 0;
    
    fprintf(stderr, "%s(): jmp_buf being set\n", __func__);
    fprintf(stderr, "%s(): calling B()\n", __func__);
    B();
    fprintf(stderr, "%s(): being normally returned from B()\n", __func__);
  }
  else
  {
    fprintf(stderr, "%s(): being returned from longjmp() from B()\n", __func__);
    //fprintf(stderr, "%s(): invoking longjmp() to B()\n", __func__);
    //longjmp(jbB, 'a');
  };
  
  fprintf(stderr, "%s(): exiting\n", __func__);
}

void B(void)
{
  fprintf(stderr, "%s(): entering\n", __func__);

  __attribute__(( cleanup(cfD) ))    // не выполнятеся
  int d = 0;
  
  if (setjmp(jbB) == 0)
  {
    __attribute__(( cleanup(cfB) ))  // не выполняется
    int b = 0;
    
    fprintf(stderr, "%s(): jmp_buf being set\n", __func__);
    fprintf(stderr, "%s(): invoking longjmp() to A()\n", __func__);
    longjmp(jbA, 'b');
  }
  else
  {
    fprintf(stderr, "%s(): being returned here from longjmp() from A()\n", __func__);
  };
  
  fprintf(stderr, "%s(): exiting\n", __func__);
}


void C(void)
{
  fprintf(stderr, "%s(): entering\n", __func__);

  __attribute__(( cleanup(cfC) ))  // выполняется
  int c = 0;                       // требуется адрес переменной для cleanup-функции, поэтому она выделяется на стеке,
                                   // и её значение сохраняется при модификации между setjump .. longjmp
  
  if (setjmp(jbC) == 0)
  {
    __attribute__(( cleanup(cfA) ))  // не выполняется
    int a = 0;
    
    fprintf(stderr, "%s(): jmp_buf being set\n", __func__);
    fprintf(stderr, "%s(): invoking longjmp() to self\n", __func__);
    longjmp(jbC, 'c');
  }
  else
  {
    __attribute__(( cleanup(cfB) )) // выполняется
    int b = 0;

    fprintf(stderr, "%s(): being returned here from longjmp()\n", __func__);
    if (++c < 10) longjmp(jbC, 'c');
  };
  
  fprintf(stderr, "%s(): exiting\n", __func__);
}


typedef int intarr10[10];

struct S { intarr10 a; };

const intarr10* f(const struct S *s) { return &s->a; }

struct S ss = { {1,} };

int main()
{
  A();
  //C();
  //return 0;
  
  PX_CATCH_AT(test);

    //__attribute__(( cleanup(cf2) ))
    int i = 0;
/*
    typedef struct S T;
    T *p = NULL;
    const T *pc = NULL;
    pc = p;
    
    (void)*p;
    (void)*pc;

    intarr10 *pa = f(&ss);
*/
    ++i;
    
    //if (i > 0) goto test;
    //longjmp(_px_ctx_obj109, 1);
    
  return 0;

test:
  switch (1 /*PX_CODE()*/)
  {
    default:
      //fprintf(stderr, "Cleanup should be done at this point.\n");
      fprintf(stderr, "%s() exiting.\n", __func__);
      break;
    case 1:
      fprintf(stderr, "%s(): PX#%i catched.\n", __func__, 1);
      C();
      break;
  };

  return 1;
}


