#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _s_stack {
  stack_elem top;
  struct _s_stack *next;
  size_t size; // Invariante de representacion,
               // size siempre mantiene el size
               // del stack, siempre >= 0
} node;

bool invrep(stack s) {
  return s->size == stack_size(s);
} // Invariante de representacion, s -> size siempre representara el tama;o

#include "stack.h"

/*
    @brief Creates an empty stack
    @return An empty stack
*/
stack stack_empty() {
  node *s = malloc(sizeof(*s));
  s->size = 0;
  s->next = NULL;

  assert(invrep(s));
  return s;
}

/*
    @brief Inserts an element at the top of the stack
    @param s A stack
    @param e An element to push into the stack
    @return The new stack with 'e' at the top
*/
stack stack_push(stack s, stack_elem e) {
  assert(invrep(s));
  node *p = NULL;

  // creo nodo
  p = malloc(sizeof(*p));
  p->top = e;
  p->next = s;
  p->size = s->size + 1; // Mantengo invrep

  assert(invrep(p)); // TODO (**) ASK
  return p;
}

/*
    @brief Removes the element at the top of the stack
    @param s A stack
    @return The new stack with the top element removed
    @note Only applies to non-empty stacks
*/
stack stack_pop(stack s) {
  assert(invrep(s));
  assert(!stack_is_empty(s));

  stack p = s;
  stack q = p->next;
  q->size = s->size - 1; // Mantengo invrep
  free(p);
  p = NULL;

  assert(invrep(q)); // TODO (**) ASK
  return q;
}

/*
    @brief Returns the size of the stack
    @param s A stack
    @return The size of the stack
*/
unsigned int stack_size(stack s) { return s->size; }

/*
    @brief Returns the element at the top of the stacks
    @param s A stacks
    @return The element at the top of the stack
    @note Only applies to non-empty stacks
*/
stack_elem stack_top(stack s) {
  assert(invrep(s));
  assert(!stack_is_empty(s));

  return s->top;
}

/*
    @brief Check if the given stack is empty
    @param s A stack
    @return true if the stack is empty, false otherwise
*/
bool stack_is_empty(stack s) {
  assert(invrep(s));
  return s->size == 0;
}

/*
    @brief Creates an array with all the elements of the stack
    @param s A stack
    @return An array containing all the elements of the stack. The stack top
    element becomes the rightmost element of the array. The size of the
    resulting array is determined by 'stack_size(s)'
*/
stack_elem *stack_to_array(stack s) {
  assert(invrep(s));

  stack_elem *array = NULL;

  if (!stack_is_empty(s)) {
    array = calloc(stack_size(s), sizeof(*array));
    node *p = s;
    for (unsigned int i = stack_size(s); i > 0; i--) {
      array[i - 1] = p->top;
      p = p->next;
    }
  }

  assert(invrep(s));
  return array;
}

/*
    @brief Destroys the stack
    @param s A stack
    @note All memory resources are freed
*/
stack stack_destroy(stack s) {
  assert(invrep(s));

  stack p = s;
  while (!stack_is_empty(p)) {
    p = stack_pop(p); // Desaloca memoria de todos los nodos excepto el vacio
  }

  assert(invrep(p)); // TODO (**) ASK
  free(p);           // <-- SI AGREGO ESTAS
  p = NULL;          // <-- DOS LINEAS SE ARREGLA
  // Debo agregar estas dos lineas porque mi stack_empty() ahora aloca memoria,
  return p;
}

void stack_dump(stack s, int a) {
  assert(invrep(s));

  stack p = s;

  if (stack_is_empty(p)) {
    printf("El stack esta vacio\n");
  }

  else {
    printf("Stack %d: (Size = %d)\n", a, stack_size(p));
    printf("   TOP\n");
    while (!stack_is_empty(p)) {
      printf("   | %d\n", stack_top(p));
      p = p->next;
      // p = stack_pop(p); // TODO ASK por que me falla hacer esto
    }
    printf("   BOTTOM\n\n");
  }

  assert(invrep(s));
}
