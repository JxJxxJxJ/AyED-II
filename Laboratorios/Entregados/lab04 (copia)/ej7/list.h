#ifndef _LIST_H
#define _LIST_H
#include <stdbool.h>

/* list as a pointer to nodes to guarantee encapsulation */
typedef struct node *list;
/* now my list is polymorphic, cool */
typedef int elem;

/* Constructors */
list empty_list();
/*
    Creates an empty list. Allocates new memory.
    Being l the returned list, is_empty(l) should be true.
*/

list addl(elem e, list l);
/*
    Adds a new element to the list l from the left.
*/

/* Destroy */
list destroy(list l);
/*
   Frees memory for list l.
*/

/* Operations */
bool is_empty(list l);
/*
    Returns whether the list l is empty.
*/

elem head(list l);
/*
    Returns a COPY of the first element from the list l.
    PRECONDITION: !is_empty(l)
*/

unsigned int length_list(list l);
/*
    Returns the list's length.
*/

elem index(list l, unsigned int n);
/*
    Returns a COPY of the n-th element from the list l.
    PRECONDITION: length(l) >= n
*/

list copy_list(list l);
/*
    Returns a COPY the list l.
*/

list tail(list l);
/*
    Removes the first element from the list l.
*/

list addr(elem e, list l);
/*
    Adds an element e to the end of the list l.
*/

list concat(list l1, list l2);
/*
   Adds to the end of the list l1 all the elements from the list l2 in the same
   order.
*/

list take(list l, unsigned int n);
/*
    Leaves in the list l the first n elements, removing the rest.
*/

list drop(list l, unsigned int n);
/*
    Removes the first n elements from the list l.
*/

void list_dump(list l);

#endif
