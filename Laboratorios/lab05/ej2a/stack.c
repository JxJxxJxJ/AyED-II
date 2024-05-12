// This seems to work, no mem leaks nor valgrind errors
// after running

#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _s_stack {
  stack_elem top;
  struct _s_stack *next;
} node;

#include "stack.h"

/*
    @brief Creates an empty stack
    @return An empty stack
*/
stack stack_empty() { return NULL; }

/*
    @brief Inserts an element at the top of the stack
    @param s A stack
    @param e An element to push into the stack
    @return The new stack with 'e' at the top
*/
stack stack_push(stack s, stack_elem e) {
  node *p = NULL;

  // creo nodo
  p = malloc(sizeof(*p));
  p->top = e;
  p->next = s;

  return p;
}

/*
    @brief Removes the element at the top of the stack
    @param s A stack
    @return The new stack with the top element removed
    @note Only applies to non-empty stacks
*/
stack stack_pop(stack s) {
  node *p = s;
  node *q = p->next;
  free(p);
  return q;
}

/*
    @brief Returns the size of the stack
    @param s A stack
    @return The size of the stack
*/
unsigned int stack_size(stack s) {
  unsigned int size = 0u;
  node *p = s;
  while (!stack_is_empty(p)) {
    size++;
    p = p->next;
  }
  return size;
}

/*
    @brief Returns the element at the top of the stacks
    @param s A stacks
    @return The element at the top of the stack
    @note Only applies to non-empty stacks
*/
stack_elem stack_top(stack s) {
  assert(!stack_is_empty(s));
  return s->top;
}

/*
    @brief Check if the given stack is empty
    @param s A stack
    @return true if the stack is empty, false otherwise
*/
bool stack_is_empty(stack s) { return s == NULL; }

/*
    @brief Creates an array with all the elements of the stack
    @param s A stack
    @return An array containing all the elements of the stack. The stack top
    element becomes the rightmost element of the array. The size of the
    resulting array is determined by 'stack_size(s)'
*/
stack_elem *stack_to_array(stack s) {
  stack_elem *array = NULL;

  if (!stack_is_empty(s)) {
    array = calloc(stack_size(s), sizeof(*array));
    node *p = s;
    for (unsigned int i = stack_size(s); i > 0; i--) {
      array[i - 1] = p->top;
      p = p->next;
    }
  }

  return array;
}

/*
    @brief Destroys the stack
    @param s A stack
    @note All memory resources are freed
*/
stack stack_destroy(stack s) {
  node *p = s;
  while (!stack_is_empty(p)) {
    p = stack_pop(p);
  }
  return p;
}

// TODO REMOVE
void stack_dump(stack s, int a) {
  if (stack_size(s) == 0) {
    printf("El stack esta vacio\n");
  } else {

    printf("Stack %d: (Size = %d)\n", a, stack_size(s));
    printf("   BOTTOM\n");

    node *p = NULL;
    p = s;

    while (p != NULL) {
      printf("   | %d\n", p->top);
      p = p->next;
    }

    printf("   TOP\n\n");
  }
}

// TODO Reversed stack, preguntar

// stack stack_empty() {
//   stack s = NULL;
//   return s; // or just return NULL
// }

// stack stack_push(stack s, stack_elem e) { // Ask
//   node *q;                                // stack node
//   node *p;                                // travel pointer

//   // create node
//   q = malloc(sizeof(node));
//   q->stack_elem = e;
//   q->next = NULL;

//   if (stack_is_empty(s)) {
//     s = q;
//   } else { // !stack_is_empty(s)
//     p = s;
//     while (p->next != NULL) {
//       p = p->next;
//     } // p -> next == NULL
//     p->next = q;
//   }
//   return s;
// }

// stack stack_pop(stack s) {    // Ask
//   assert(!stack_is_empty(s)); // stack_size != 0
//   node *p = NULL;             // recorro con p
//   node *q = NULL;             // libero el ultimo nodo con q

//   if (stack_size(s) == 1) {
//     p = s;
//     s = stack_empty();
//     free(p);
//   }

//   else { // stack_size(s) >= 2
//     p = s;
//     while (p->next->next != NULL) {
//       p = p->next;
//     }
//     // aqui p -> next -> next == NULL
//     //     [ | ] --> [ | ] -> NULL
//     // p ----^

//     q = p->next;
//     //     [ | ] --> [ | ] -> NULL
//     // p ----^   q-----^

//     p->next = NULL;
//     //     [ | ]  --> NULL    [ | ] -> NULL
//     // p ----^            q ----^

//     free(q);
//     //     [ | ]  --> NULL
//     // p ----^            q ----^

//     q = NULL;
//     //     [ | ]  --> NULL     NULL
//     // p ----^            q ----^
//   }

//   return s;
// }

// unsigned int stack_size(stack s) { // Ask
//   unsigned int size = 0u;
//   node *p;
//   p = s;
//   while (p != NULL) {
//     size++;
//     p = p->next;
//   }
//   return size;
// }

// stack_elem stack_top(stack s) { // ASK
//   assert(!stack_is_empty(s));
//   node *p;
//   p = s;
//   while (p->next != NULL) {
//     p = p->next;
//   } // p -> next == NULL
//   return p->stack_elem;
// }

// bool stack_is_empty(stack s) { return s == NULL; }

// stack_elem *stack_to_array(stack s) { // ASK
//   stack_elem *array = NULL;

//   if (!stack_is_empty(s)) {
//     array = malloc(sizeof(*array) * stack_size(s));

//     node *p;
//     p = s;

//     for (unsigned int i = 0u; i < stack_size(s); i++) {
//       array[i] = p->stack_elem;
//       p = p->next;
//     }
//   }

//   return array;
// }

// stack stack_destroy(stack s) { // Ok
//   node *p;
//   while (s != NULL) {
//     p = s;
//     s = s->next;
//     free(p);
//   }
//   return s;
// }

// void stack_dump(stack s, int a) {
//   if (stack_size(s) == 0) {
//     printf("El stack esta vacio\n");
//   } else {

//     printf("Stack %d: (Size = %d)\n", a, stack_size(s));
//     printf("   BOTTOM\n");

//     node *p = NULL;
//     p = s;

//     while (p != NULL) {
//       printf("   | %d\n", p->stack_elem);
//       p = p->next;
//     }

//     printf("   TOP\n\n");
//   }
// }
