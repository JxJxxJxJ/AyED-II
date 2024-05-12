#include "stack.h"
#include <assert.h>
#include <stdlib.h>

#include <stdio.h> // TODO REMOVE

#define INITIAL_CAPACITY 10 // arbitrario

struct _s_stack {
  stack_elem *elems;     // Arreglo de elementos
  unsigned int size;     // Cantidad de elementos en la pila
  unsigned int capacity; // Capacidad actual del arreglo elems
  // Invrep:
  // s->size ==  stack_size(s);
  // s->size <= s->capacity
};

bool invrep(stack s) {
  assert(s != NULL); // NOTE VERSION 1
  bool b_invrep =
      s->size == stack_size(s) && s->size <= s->capacity; // NOTE VERSION 1

  // bool b_invrep = true; // NOTE VERSION 2
  // if (s != NULL) {
  //   b_invrep = s->size == stack_size(s) && s->size <= s->capacity;
  // }
  // else {
  // ??????
  // }

  return b_invrep;
}

/**
 * @brief Creates an empty stack
 * @return An empty stack
 */
stack stack_empty() { // Allocates memory for the struct only
  stack s = malloc(sizeof(*s));
  s->elems = NULL;
  s->size = 0;
  s->capacity = INITIAL_CAPACITY;
  assert(invrep(s));
  return s;
}

/**
 * @brief Inserts an element at the top of the stack
 * @param s A stack
 * @param e An element to push into the stack
 * @return The new stack with 'elem' at the top
 */
stack stack_push(stack s, stack_elem e) {
  assert(invrep(s));
  size_t array_slot_size = s->capacity * sizeof(*s->elems);

  if (stack_is_empty(s)) {
    s->elems = realloc(s->elems, array_slot_size); // doubles array's
  }

  else if (!stack_is_empty(s)) {
    if (s->size == s->capacity) { // ask for more memory if needed for the array
      s->elems = realloc(s->elems, array_slot_size * 2); // doubles array's
      s->capacity = s->capacity * 2;                     // capacity
    };
  }

  s->elems[s->size] = e; // adds element onto the array;
  s->size++;             // preserves invrep(s)
  assert(invrep(s));
  return s;
}

/**
 * @brief Removes the element at the top of the stack
 * @param s A stack
 * @return The new stack with the top element removed
 * @note Only applies to non-empty stacks
 */
stack stack_pop(stack s) { // pop [4]
  assert(!stack_is_empty(s));
  assert(invrep(s));
  s->elems[s->size - 1] = 0; // "deletes" element placing 0, unnecessary
  s->size--;                 // preserves invrep(s)
  assert(invrep(s));
  return s;
}

/**
 * @brief Returns the size of the stack
 * @param s A stack
 * @return The size of the stack
 */
unsigned int stack_size(stack s) { return s->size; }

/**
 * @brief Returns the element at the top of the stacks
 * @param s A stacks
 * @return The element at the top of the stack
 * @note Only applies to non-empty stacks
 */
stack_elem stack_top(stack s) {
  assert(invrep(s));
  assert(!stack_is_empty(s));
  return s->elems[s->size - 1]; // [e] has e in position 0, but has size 1
}

/**
 * @brief Check if the given stack is empty
 * @param s A stack
 * @return true if the stack is empty, false otherwise
 */
bool stack_is_empty(stack s) {
  assert(invrep(s));
  return s->size == 0;
}

/**
 * @brief Creates an array with all the elements of the stack
 * @param s A stack
 * @return An array containing all the elements of the stack. The stack top
 * element becomes the rightmost element of the array. The size of the
 * resulting array is determined by 'stack_size(s)'
 */
stack_elem *stack_to_array(stack s) {
  assert(invrep(s));
  stack_elem *array = malloc(sizeof(*array) * stack_size(s));
  for (unsigned int i = 0; i < stack_size(s); i++) {
    array[i] = s->elems[i];
  }
  assert(invrep(s));
  return array; // dynamic array, must free later
}

/**
 * @brief Destroys the stack
 * @param s A stack
 * @note All memory resources are freed
 */
stack stack_destroy(stack s) {
  assert(invrep(s));
  free(s->elems);
  s->elems = NULL;
  free(s);
  s = NULL;

  // assert(invrep(s)); // NOTE VERSION 1 YES COMMENT
  // assert(invrep(s)); // NOTE VERSION 2 NO COMMENT
  return s;
}

// TODO REMOVE

void stack_dump(stack s, int a) {
  if (stack_is_empty(s)) {
    printf("El stack está vacío\n");
  } else {
    printf("Stack %d: (Size = %d)\n", a, stack_size(s));
    printf("   TOP\n");
    stack_elem *array = stack_to_array(s);
    for (int i = stack_size(s) - 1; i >= 0; i--) {
      printf("   | %d\n", array[i]);
    }
    free(array);
    printf("   BOTTOM\n\n");
  }
}
