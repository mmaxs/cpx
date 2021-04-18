
/* gcc -std=c11 -Wall -Wpedantic -pedantic-errors -D_DEFAULT_SOURCE  cleanup-test.c  -o cleanup-test */

#include <stdlib.h>
#include <stdio.h>


struct Obj { int x; };

void Obj_cleanup(struct Obj **obj_ref)
{
  fprintf(stdout, "%s() for %p\n", __func__, (void*)(*obj_ref));
  fflush(stdout);
  free(*obj_ref);
}


int main(void)
{
  {
    struct Obj *test __attribute__(( cleanup(Obj_cleanup) )) = calloc(1, sizeof(struct Obj));
    fprintf(stdout, "Obj allocated at %p\n", (void*)test);
    
    fprintf(stdout, "Quitting the test scope...\n");
    goto main__sub1;
  
main__exit:
    return 0;
  } // <-- Obj_cleanup is executed here twice, even though the control flow passes the 'test' definition only once

main__sub1:
  fprintf(stdout, "The test scope has been quit.\n");
  goto main__exit;
}

