#include <stdio.h>

#include "stack.h"

int main() {
  stack s = stack_empty();
  printf("El stack %s\n", (stack_is_empty(s) ? "esta vacio" : "NO esta vacio"));

  int x = 10;
  s = stack_push(s, 1);
  s = stack_push(s, 2);
  s = stack_push(s, 3);
  stack_dump(s, 1);

  s = stack_empty();
  s = stack_push(s, 10);
  s = stack_push(s, 5);
  s = stack_push(s, 3);
  s = stack_push(s, 2);
  stack_dump(s, 2);

  s = stack_empty();
  s = stack_push(s, x * 2);
  s = stack_push(s, x * 2);
  s = stack_push(s, x);
  s = stack_push(s, x * 3);
  stack_dump(s, 3);

  return 0;
}
