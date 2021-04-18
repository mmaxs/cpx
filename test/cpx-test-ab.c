
//* CFLAGS += -Wall -Wpedantic -pedantic-errors

#include <stdio.h>
#include <locale.h>
#include "px.h"


jmp_buf jbA, jbB, jbC, jbD;

void cfA(volatile int* _)  { printf("*** executing %s()\n", __func__); }
void cfB(int* _)  { printf("*** executing %s()\n", __func__); }
void cfC(int* _)  { printf("*** executing %s()\n", __func__); }
void cfD(int* _)  { printf("*** executing %s()\n", __func__); }


void B(void);

void A(void)
{
  printf("%s(): entering\n", __func__);
  {  //! (0)
    int d __attribute__(( cleanup(cfD) )) = 0;  //! (1), выполняется после перехвата и выходе из области выдимости (0)

    PX_CATCH_AT(px);

    volatile int a __attribute__(( cleanup(cfA) )) = 0;  //! (2), НЕ выполняется после перехвата, спецификатор volatile никак не помогает

    printf("%s(): PX_CATCH_AT() being set\n", __func__);
    printf("%s(): calling B()\n", __func__);
    B();
    printf("%s(): being normally returned from B()\n", __func__);
  //}  //! если стереть эти границы области видимости (0), то (2) тоже выполняется при выходе из функции

exit:
  printf("%s(): exiting\n", __func__);
  return;
  }  //! если перенести границу сюда, то (2) выполнится, и (1) ВЫПОЛНИТСЯ ВТОРОЙ РАЗ; всё из-за 'goto exit' (3)

px:;
  int x = *PX();
  switch (x)
  {
    case 'b': printf("%s(): exception catched: '%c' from <%s(),%s>\n", __func__, x, PX_SRCFUNC(), PX_SRCLINE());
              //PX_RETHROW();
              goto exit;  //! (3)
              break;
     default: printf("%s(): exception catched: '%c' from <%s(),%s>\n", __func__, x, PX_SRCFUNC(), PX_SRCLINE());
              //goto exit;
              break;
  };
}

void B(void)
{
  printf("%s(): entering\n", __func__);

  int b __attribute__(( cleanup(cfB) )) = 0;  //! не выполняется
  
  printf("%s(): doing THROW('b')\n", __func__);
  PX_THROW('b');
  
  printf("%s(): exiting\n", __func__);
}


void C(void)
{
{
  printf("%s(): entering\n", __func__);

  int c __attribute__(( cleanup(cfC) )) = 0;  //! выполняется
  
  printf("%s(): doing THROW_TO(cleanup, 'c')\n", __func__);
  PX_THROW_TO(cleanup, 'c');
  
  printf("%s(): exiting\n", __func__);
  return;
}
cleanup:
  PX_RETHROW();
}


int main()
{
  setvbuf(stdout, NULL, _IONBF, 0);

  printf("%s\n", setlocale(0, NULL));
  printf("%s\n", "тест");

  //PX_CATCH_AT(uncaught_x);
  
  A();
  C();
  
  return 0;

uncaught_x:
  printf("%s(): uncaught exception: '%c' from <%s(),%s>\n", __func__, *PX(), PX_SRCFUNC(), PX_SRCLINE());
  return 1;          
}


