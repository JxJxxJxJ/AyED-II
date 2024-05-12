#include "stack.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
  printf("Inicializo el stack en stack_empty para comenzar a realizar los "
         "testeos\n");
  stack s = stack_empty();

  printf("-------------------------------------------------\n");
  printf("Test Case 1: stack_pop() sobre una pila de tamaño 1\n"); // TEST OK
  s = stack_empty();
  s = stack_push(s, 4);
  printf("Stack con 1 elemento: \n");
  stack_dump(s, 1);
  printf("Hago stack_pop al stack con 1 elemento: \n");
  s = stack_pop(s);
  stack_dump(s, 1);
  printf("-------------------------------------------------\n");

  s = stack_destroy(s);

  printf("----------------------------------------\n");
  printf("Test Case 2: stack_push() a una pila vacia\n"); // TEST OK
  s = stack_empty();
  printf("Stack vacio con 0 elementos");
  stack_dump(s, 2);
  printf("Hago stack_push");
  s = stack_push(s, 4);
  stack_dump(s, 2);
  printf("----------------------------------------\n");

  s = stack_destroy(s);

  printf("----------------------------------------------------------\n");
  printf("Test Case 3: stack_to_array() da NULL en la pila vacia? \n"
         "Devuelve los elementos en el orden correcto?\n"); // TEST OK
  s = stack_empty();
  printf("Stack vacio con 0 elementos\n");
  printf("Hago stack_to_array\n");
  stack_elem *array = stack_to_array(s);
  printf("La direccion de array es %p\n", (void *)array);
  printf("----------------------------------------------------------\n");
  return 0;
}
