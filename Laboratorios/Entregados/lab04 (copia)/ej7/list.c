#include "list.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  elem elem;
  struct node *next;
} node; // typedef required a name...

/* Constructors */
list empty_list() { // CHECK c Fer
  list l = NULL;
  return l;
}
/*
    Creates an empty list. Allocates new memory.
    Being l the returned list, is_empty(l) should be true.
*/

list addl(elem e, list l) {
  node *p;
  p = malloc(sizeof(node));
  p->elem = e;
  p->next = l;
  l = p;
  return l;
}
/*
    Adds a new element to the list l from the left.
*/

/* Destroy */
list destroy(list l) {
  while (l != NULL) {
    node *p = l;
    l = l->next;
    free(p);
  }
  return NULL;
}
/*
   Frees memory for list l.
*/

/* Operations */
bool is_empty(list l) { return l == NULL; } // Ok
/*
    Returns whether the list l is empty.
*/

elem head(list l) { // Ok
  assert(!is_empty(l));
  node *p;
  p = malloc(sizeof(node));
  p->elem = l->elem;
  return p->elem;
}
/*
    Returns a COPY of the first element from the list l.
    PRECONDITION: !is_empty(l)
*/

unsigned int length_list(list l) { // Ok
  node *p;
  unsigned int n = 0;
  p = l;
  while (p != NULL) {
    n = n + 1;
    p = p->next;
  }
  return n;
}

elem index(list l, unsigned int n) { // ok
  assert(length_list(l) > n);
  node *p;
  p = malloc(sizeof(node));
  p = l;
  unsigned int i = 0u;
  while (i < n) {
    p = p->next;
    i++;
  }
  return p->elem;
}

list copy_list(list l) {
  node *copy;
  //   list copy = empty_list();
  copy = NULL;
  //   list p = l;
  node *p;
  p = l;
  while (p != NULL) {
    // copy = addr(p->elem, copy);
    node *Node;
    Node = malloc(sizeof(node));
    Node->elem = p->elem;
    Node->next = NULL;
    if (!is_empty(copy)) {
      node *ptr;
      ptr = copy;
      while (ptr->next != NULL) {
        ptr = ptr->next;
      }
      ptr->next = Node;
    } else {
      copy = Node;
    };
    //  p = p->next;
    p = p->next;
  }
  return copy;
}
/*
    Returns a COPY the list l.
*/

list tail(list l) {
  l = l->next;
  return l;
}
/*
    Removes the first element from the list l.
*/

list addr(elem e, list l) { // Ok
  node *p;
  node *q;

  // I create a node q
  q = malloc(sizeof(node));
  q->elem = e;
  q->next = NULL;

  if (!is_empty(l)) {
    p = l;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = q;
  } else {
    l = q;
  }
  return l;
}
/*
    Adds an element e to the end of the list l.
*/

list concat(list l1, list l2) { // Ok
  node *p = l1;
  while (p->next != NULL) {
    p = p->next;
  }
  p->next = l2;
  return l1;
}
/*
   Adds to the end of the list l1 all the elements from the list l2 in the
   same order.
*/

list take(list l, unsigned int n) { // Ok
  node *p;
  p = l;
  unsigned int i = 0u;
  while (i < n && p->next != NULL) {
    p = p->next;
    i++;
  }
  // i = n
  destroy(p->next); // destroy(p->next) destruye los elementos
                    // en las posiciones n+1 en adelante
  return l;
}
/*
    Leaves in the list l the first n elements, removing the rest.
*/

list drop(list l, unsigned int n) { // ok
  node *p;
  unsigned int i = 0;
  while (i < n && p->next != NULL) {
    p = l;
    l = l->next;
    free(p);
    i++;
  }
  return l;
}
/*
    Removes the first n elements from the list l.
*/

void list_dump(list l) {
  printf("\n\nList elements are: \n");
  list l_copy = copy_list(l);
  while (l_copy != NULL) {
    printf("%d ---> ", l_copy->elem);
    l_copy = l_copy->next;
  }
}
/*
    Prints the list, not part of the specification but useful
*/
