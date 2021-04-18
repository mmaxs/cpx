
#include <stdio.h>
#include "px.h"


void bar(int n)
{
  if (n == 4)
  {
    printf("%s: *** throw an exception: '%i'\n", __func__, n);
    PX_THROW(n);
  };
}

/* No tail call optimization performed for this function because of
   the implicit cleanup function call at the end of the function. */
void foo_tail_recursion(int n)
{
  if (n >= 5) return;

  goto start;
x_handler:
  printf("%s: *** exception caught: '%i' from <%s(),%s>\n", __func__, *PX(), PX_SRCFUNC(), PX_SRCLINE());
  return;
  
start:
  printf("%s: level %i\n", __func__, n);
  printf("%s: | set PX_CATCH and invoke bar()\n", __func__);
  
  PX_CATCH_AT(x_handler)
  bar(n);

  printf("%s: | go to the next level...\n", __func__);
  foo_tail_recursion(n + 1);
}


int main()
{
  setvbuf(stdout, NULL, _IONBF, 0);

  foo_tail_recursion(0);

  return 0;
}

