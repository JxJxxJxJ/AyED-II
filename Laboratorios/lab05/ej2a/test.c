#include <stdio.h>

#include "stack.h"

int main() {
  stack s = stack_empty();
  stack_dump(s, 0);

  printf("El stack %s\n", (stack_is_empty(s) ? "esta vacio" : "NO esta vacio"));

  s = stack_push(s, 1);
  stack_dump(s, 1);

  stack_pop(s);
  stack_dump(s, 2);

  s = stack_push(s, 2);
  s = stack_push(s, 3);
  stack_dump(s, 3);

  stack_pop(s);
  stack_dump(s, 4);
  stack_pop(s);
  stack_dump(s, 4);
  stack_pop(s);
  stack_dump(s, 4);

  stack_destroy(s);

  return 0;
}
