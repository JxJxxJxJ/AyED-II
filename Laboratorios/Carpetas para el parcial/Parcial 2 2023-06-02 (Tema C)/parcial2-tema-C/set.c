#include "set.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct s_node {
  set_elem elem;
  struct s_node *next;
};

typedef struct s_node *node_t;

struct s_set {
  unsigned int size;
  node_t first;
};

static bool invrep(set s) {
  bool b = false;
  if (s != NULL) {
    b = true;
    if (s->first != NULL && s->size != 0) {
      node_t p = s->first;
      while (b && p->next != NULL) {
        b = b && p->elem < p->next->elem;
        p = p->next;
      }
    } 
  }   
  return b;
}

static struct s_node *create_node(set_elem e) {
  node_t node = malloc(sizeof(*node));
  node->elem = e;
  node->next = NULL;
  return node;
}

static struct s_node *destroy_node(struct s_node *node) {
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

/* CONSTRUCTORS */
set set_empty(void) {
  set s = malloc(sizeof(*s));
  s->first = NULL;
  s->size = 0u;
  return s;
}

/*
 Adds element <e> element to the set <s>. If <e> was already in <s>
 the function makes no changes.

 PRE: {s --> set}

 s = set_add(s, e);

 POS: {s --> set && !set_is_emtpy(s)}
*/
set set_add(set s, set_elem e) {
  assert(invrep(s));
  node_t previous_node = NULL; // puntero al nodo #"x-1"
  node_t node = s->first; // Puntero al nodo #"x" (Donde x va hasta s->size)

  // Caso 0:
  // Si el set esta vacio es trivial agregar el nuevo nodo
  if (set_is_empty(s)) {
    s->first = create_node(e);
    s->size++;
  } else {
    // Caso 0.1:
    // Si e ya pertenece al set, no hay que agregarlo
    if (set_member(e, s)) {
      // skip
    }
    if (!set_member(e, s)) {
      // Avanzamos hasta llegar al nodo con el primer elemento de mayor valor
      // O hasta el final del set
      while (node->next != NULL && (node->elem < e)) {
        previous_node = node;
        node = node->next;
      } // node -> elem > e

      // Caso 1: No hay nodo previo
      if (previous_node == NULL) {

        // [2] meto el 4
        // Caso 1.1:
        // 'e' es mayor que el elemento del set
        if (node->next == NULL && (node->elem < e)) {
          s->first->next = create_node(e);
          s->size++;
        }

        // [2] meto el 1
        // [1, 2] meto el 1
        // Caso 1.2:
        // Hay un elemento mayor que 'e'
        if (!(node->elem < e)) {
          node_t new_node = create_node(e);
          new_node->next = s->first;
          s->first = new_node;
          s->size++;
        }
      }

      else {
        // [2,3] 4
        // [2,3,4] 4
        // Caso 2: Hay nodo previo
        // Caso 2.1:
        // 'e' es mayor al elemento que estamos mirando
        if (node->elem < e) {
          node_t new_node = create_node(e);
          new_node->next = node->next;
          node->next = new_node;
          s->size++;
        }

        else if (!(node->elem < e)) {
          // [2,3,   5,6] 4
          //    prev p
          // Caso 2.2:
          // 'e' es menor al elemento que estamos mirando actualmente
          node_t new_node = create_node(e);
          new_node->next = node;
          previous_node->next = new_node;
          s->size++;
        }
      }
    }
  }
  /*
   a b c d f g meto la e
   node_t node = create_node(e);
   while (p -> elem < e){
      prev = p;
      p = p -> next
   } // p->elem >= e
   a b c d    f g meto la e
         prev p
   node -> next = p;
   previous -> next = node;
   a b c d  f g
         |  ^
         |->e
   a b c d e f g
   */
  //

  return s;
}

/*
 Returns how many elements are in <s>

 PRE: {s --> set}

 n = set_cardinal(s);

 POS: {(n == 0) == set_is_empty(s)}
*/
unsigned int set_cardinal(set s) {
  assert(invrep(s));
  return s->size;
  assert((s->size == 0) == set_is_empty(s));
}

/*
 Indicates if the set <s> is empty.

 PRE: {s --> set}

 b = set_is_empty(s);

*/
bool set_is_empty(set s) {
  assert(invrep(s));
  return s->size == 0;
}

bool set_member(set_elem e, set s) {
  assert(invrep(s));
  node_t node = s->first;
  while (node != NULL && node->elem < e) {
    node = node->next;
  }
  return node != NULL && node->elem == e;
}

/*
 Indicates if the element <e> belongs to the set <s>.

 PRE: {s --> set}

 b = set_member(e, s);

*/
set set_elim(set s, set_elem e) {
  assert(invrep(s));
  if (!set_member(e, s)) {
    // skip
  } else if (set_member(e, s)) {
    node_t p = s->first;
    if (p->elem == e) {
      s->first = s->first->next;
      destroy_node(p);
    } else if (p->elem != e) {
      while (p->next->elem != e) {
        p = p->next;
      } // p -> next -> elem == e
      node_t killme = p->next;
      p->next = p->next->next;
      destroy_node(killme);
    }
  };
  s->size--;
  return s;
}

set_elem set_get(set s) {
  assert(invrep(s) && !set_is_empty(s));
  return s->first->elem;
}

/*
 Return an array with all elements that belong to <s>.

 The returned array is stored in dynamic memory and has enough room for
 `set_cardinal(s)` elements. The caller must free the memory.

 PRE: {s --> set}

 array = set_to_array(s);

 POS: {!set_is_empty(s) ==> (array!=NULL)
 POS: {p                ==> q}
 POS: {!p || (p && q)}

*/
set_elem *set_to_array(set s) {
  assert(invrep(s));
  set_elem *array = malloc(sizeof(*array) * set_cardinal(s));
  node_t p = s->first;

  for (unsigned int i = 0u; i < set_cardinal(s); i++) {
    array[i] = p->elem;
    p = p->next;
  }
  assert(set_is_empty(s) || (!set_is_empty(s) && array != NULL));
  return array;
}

/*
 Destroy the set <s> freeing all memory used by the data structure

 PRE: {s --> set}
 s = set_destroy(s);

 POS: {s == NULL}
*/
set set_destroy(set s) {
  assert(invrep(s));
  while (!set_is_empty(s)) {
    s = set_elim(s, set_get(s));
  }
  free(s);
  s = NULL;
  assert(s == NULL);
  return s;
}
