
#include <stdio.h>
#include <setjmp.h>


jmp_buf jbA, jbB, jbC, jbD;

void cfA(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }
void cfB(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }
void cfC(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }
void cfD(int* _)  { fprintf(stderr, "*** Executing %s().\n", __func__); }


void B(void);

void A(void)
{
  fprintf(stderr, "%s(): entering\n", __func__);

  __attribute__(( cleanup(cfC) ))     //! выполняется при longjmp из B() и последующем выходе из ф-ции
  int c = 0;

  if (setjmp(jbA) == 0)
  {
    __attribute__(( cleanup(cfA) ))   //! не выполняется при longjmp из B() и последующем выходе из ф-ции
    int a = 0;
    
    fprintf(stderr, "%s(): jmp_buf being set\n", __func__);
    fprintf(stderr, "%s(): calling B()\n", __func__);
    B(); 
    fprintf(stderr, "%s(): being normally returned from B()\n", __func__);
  }
  else
  {
    fprintf(stderr, "%s(): being returned from longjmp() from B()\n", __func__);

    //! На такой попытке программа молча падает.
    fprintf(stderr, "%s(): invoking longjmp() to B()\n", __func__);
    fflush(stderr);
    longjmp(jbB, 'a');
  };
  
  fprintf(stderr, "%s(): exiting\n", __func__);
}

void B(void)
{
  fprintf(stderr, "%s(): entering\n", __func__);

  __attribute__(( cleanup(cfD) ))     //! не выполнятеся при (1)
  int d = 0;
  
  if (setjmp(jbB) == 0)
  {
    __attribute__(( cleanup(cfB) ))   //! не выполняется при (1)
    int b = 0;
    
    fprintf(stderr, "%s(): jmp_buf being set\n", __func__);
    fprintf(stderr, "%s(): invoking longjmp() to A()\n", __func__);
    longjmp(jbA, 'b');                //! (1)
  }
  else
  {
    fprintf(stderr, "%s(): being returned here from longjmp() from A()\n", __func__);
  };
  
  fprintf(stderr, "%s(): exiting\n", __func__);
}


int main()
{
  A();
  
  return 0;
}


