#include "pstack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <threads.h>

struct s_pstack {
  struct s_node **elems;     // elems es un puntero (arreglo) de punteros a nodo
  unsigned int size;         // Cantidad de elementos en la pila
  unsigned int max_priority; // Capacidad del arreglo elems
};

struct s_node {
  pstack_elem elem;
  struct s_node *next;
};

static struct s_node *create_node(pstack_elem e) { // ALOCA MEMORIA
  struct s_node *new_node = malloc(sizeof(*new_node));
  assert(new_node != NULL);
  new_node->elem = e;
  new_node->next = NULL;
  return new_node;
}

static struct s_node *destroy_node(struct s_node *node) { // LIBERA MEMORIA
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

static bool invrep(pstack s) { return s != NULL; }

/*
 * DESC: Creates a new instance of pstack with 'max_priority' limit
 *
 * PRE: {true}
 *  s = pstack_empty();
 * POS: {s --> pstack && pstack_is_empty(s)}
 *
 */
pstack pstack_empty(priority_t max_priority) { // ALOCA MEMORIA
  pstack s = malloc(sizeof(*s));
  s->max_priority = max_priority;
  s->size = 0;
  s->elems = calloc(sizeof(s->elems),
                    s->max_priority + 1); // Lo inicializo en 0s o NULL
  assert(invrep(s));
  assert(pstack_is_empty(s));
  return s;
}

/*
 * DESC: Adds element 'e' into the pstack 's' with the given 'priority'
 *
 *
 * PRE: {s --> pstack && priority <= s --> max_priority }
 *  s = pstack_push(s, e, priority);
 * POS: {s --> pstack && !pstack_is_empty(s)}
 *
 */
pstack pstack_push(pstack s, pstack_elem e, priority_t priority) { // TODO check
  assert(invrep(s));
  assert(priority <= s->max_priority);
  struct s_node *nodo = create_node(e); // ALOCA MEMORIA
  /*
  s-------->   {elems            size               max_priority}
          --------+--------
          ' ------+----   |
          ' '     v   |   |
          ' ' ---[p0, p1, p2]
          ' ' '
          ' ' '-> NULL
          ' '---> NULL
          '-----> [200 | ] -> [100 | ] -> NULL
          p--------------------^
  */

  if (s->elems[priority] != NULL) {

    struct s_node *p = s->elems[priority]; // Aqui guardo la direccion del viejo
                                           // top de esa priority
    s->elems[priority]->elem = nodo->elem;
    s->elems[priority]->next = p;
  }

  else if (s->elems[priority] == NULL) {
    s->elems[priority] = nodo;
  }

  s->size++;
  assert(invrep(s));
  assert(!pstack_is_empty(s));
  return s;
}

/*
 * DESC: Indicates whether the pstack 's' is empty or not
 *
 */
bool pstack_is_empty(pstack s) {
  assert(invrep(s));
  return s->size == 0u;
}

/*
 * DESC: Return the element with the most urgent prioritiy of the pstack 's'
 *
 * PRE: {s --> pstack && !pstack_is_empty(s)}
 *  e = pstack_top(s);
 * POS: {s --> pstack}
 */
pstack_elem pstack_top(pstack s) { // TODO check
  assert(invrep(s));
  assert(!pstack_is_empty(s));

  pstack_elem elemento = s->elems[pstack_top_priority(s)]->elem;

  assert(invrep(s));
  return elemento;
}

/*
 * DESC: Return the element with the most urgent prioritiy of the pstack 's'
 *
 * PRE: {s --> pstack && !pstack_is_empty(s)}
 *  e = pstack_top(s);
 * POS: {s --> pstack}
 */
priority_t pstack_top_priority(pstack s) {
  assert(invrep(s));
  assert(!pstack_is_empty(s));

    unsigned int max = 0u;
    for (unsigned int i = 0; i <= s->max_priority; i++) {
      if (s->elems[i] != NULL) {
        max = i;
      } else if (s->elems[i] == NULL) {
        // skip
      }
    }

//   int i = s->max_priority;
//   while (i >= 0) {
//     if (s->elems[i] != NULL) {
//       return s->elems[i]->elem;
//     }
//     i--;
//   }
//   return 0;

  assert(invrep(s));
    return max;
}

/*
 * DESC: Return the number of elements inside the pstack 's'
 *
 */
size_t pstack_size(pstack s) {
  assert(invrep(s));
  return s->size;
}

/*
 * DESC: Remove the element with the most urgent priority of the pstack 's'
 *
 * PRE: {s --> pstack && !pstack_is_empty(s)}
 *  q = pstack_pop(q);
 * POS: {s --> pstack}
 *
 */
pstack pstack_pop(pstack s) {
  assert(invrep(s));
  assert(!pstack_is_empty(s));

  struct s_node *killme = NULL;
  killme = s->elems[pstack_top_priority(s)];

  s->elems[pstack_top_priority(s)] = s->elems[pstack_top_priority(s)]->next;
  destroy_node(killme);

  s->size--;
  assert(invrep(s));
  return s;
}
/*
 * DESC: Destroy instance of pstack, freeing all memory used by 's'.
 *
 * PRE: {s --> pstack}
 *  s = pstack_destroy(s);
 * POS: {s == NULL}
 *
 */
pstack pstack_destroy(pstack s) {
  assert(invrep(s));
  struct s_node *killme = NULL;
  for (unsigned int i = 0u; i <= s->max_priority; i++) {
    killme = s->elems[i];
    while (s->elems[i] != NULL) {
      killme = s->elems[i];
      s->elems[i] = s->elems[i]->next;
      destroy_node(killme);
    }
  }

  free(s->elems);
  free(s);
  s = NULL;

  assert(s == NULL);
  return s;
}
