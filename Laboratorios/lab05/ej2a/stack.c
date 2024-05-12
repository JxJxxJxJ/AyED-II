// This seems to work, no mem leaks nor valgrind errors
// after running

#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _s_stack {
  stack_elem stack_elem;
  struct _s_stack *next;
} node;

#include "stack.h"

stack stack_empty() {
  stack s = NULL;
  return s; // or just return NULL
}

stack stack_push(stack s, stack_elem e) { // Ask
  node *q;                                // stack node
  node *p;                                // travel pointer

  // create node
  q = malloc(sizeof(node));
  q->stack_elem = e;
  q->next = NULL;

  if (stack_is_empty(s)) {
    s = q;
  } else { // !stack_is_empty(s)
    p = s;
    while (p->next != NULL) {
      p = p->next;
    } // p -> next == NULL
    p->next = q;
  }
  return s;
}

stack stack_pop(stack s) {    // Ask
  assert(!stack_is_empty(s)); // stack_size != 0
  node *q = NULL;
  node *p = NULL;
  p = s;
  if (stack_size(s) == 1) {
    s = stack_empty();
    free(p);
    p = NULL;
  } else { // stack_size(s) >= 2
    while ((p->next)->next != NULL) {
      p = s;
      p = p->next;
    } // (p -> next) -> next == NULL
  }
  q = p->next;
  p->next = NULL;
  free(q);
  return s;
}

unsigned int stack_size(stack s) { // Ask
  unsigned int size = 0u;
  node *p;
  p = s;
  while (p != NULL) {
    size++;
    p = p->next;
  }
  return size;
}

stack_elem stack_top(stack s) { // ASK
  node *p;
  p = s;
  while (p->next != NULL) {
    p = p->next;
  } // p -> next == NULL
  return p->stack_elem;
}

bool stack_is_empty(stack s) { return s == stack_empty(); }

stack_elem *stack_to_array(stack s) { // ASK
  stack_elem *array = malloc(sizeof(*array) * stack_size(s));
  return array;
}

stack stack_destroy(stack s) { // Ok
  node *p;
  while (s != NULL) {
    p = s;
    s = s->next;
    free(p);
  }
  return s;
}

void stack_dump(stack s, int a) {
  if (stack_size(s) == 0) {
    printf("El stack esta vacio\n");
  } else {

    printf("Stack %d: (Size = %d)", a, stack_size(s));
    printf("   BOTTOM\n");

    node *p = NULL;
    p = s;

    while (p != NULL) {
      printf("   | %d\n", p->stack_elem);
      p = p->next;
    }

    printf("   TOP\n\n");
  }
}
