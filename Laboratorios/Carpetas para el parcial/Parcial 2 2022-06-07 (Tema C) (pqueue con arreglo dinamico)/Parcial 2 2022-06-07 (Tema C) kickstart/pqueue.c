#include "pqueue.h"
#include "queue.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct s_node *node_t;

struct s_pqueue {
  node_t *array;
  unsigned int min_priority;
  size_t size;
};

struct s_node {
  queue_elem elem;
  node_t next;
};

static struct s_node *create_node(pqueue_elem e) {
  node_t new_node = malloc(sizeof(*new_node));
  assert(new_node != NULL);
  new_node->elem = e;
  new_node->next = NULL;
  return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

static bool invrep(pqueue q) {
  bool b = q != NULL;
  return b;
}

/*
 * DESC: Creates a new instance of pqueue with 'min_priority' limit
 *       This pqueue couldn't store elements with priority > min_priority
 *
 * PRE: {true}
 *  q = pqueue_empty();
 * POS: {q --> pqueue && pqueue_is_empty(q)}
 *
 */
pqueue pqueue_empty(priority_t min_priority) {
  pqueue q = malloc(sizeof(*q));
  q->array = calloc(min_priority + 1, sizeof(*q->array));
  q->min_priority = min_priority;
  q->size = 0;
  assert(invrep(q));
  assert(pqueue_is_empty(q));
  return q;
}

/*
 * DESC: Adds element 'e' into the pqueue 'q' with the given 'priority'
 *
 * PRE: {q --> pqueue && priority <= q--> min_priority}
 *  q = pqueue_enqueue(q, e, priority);
 * POS: {q --> pqueue && !pqueue_is_empty()}
 *
 */
pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
  assert(invrep(q));
  assert(priority <= q->min_priority);
  node_t new_node = create_node(e); // mando al node al fondo
  if (q->array[priority] == NULL) {
    q->array[priority] = new_node;
  }

  else if (q->array[priority] != NULL) {
    node_t p = q->array[priority]; // comienzo de la cola
    while (p->next != NULL) {
      p = p->next;
    } // aqui p -> next = NULL
    p->next = new_node;
  }
  q->size++;
  assert(invrep(q) && !pqueue_is_empty(q));
  return q;
}

/*
 * DESC: Indicates whether the pqueue 'q' is empty or not
 *
 */
bool pqueue_is_empty(pqueue q) {
  assert(invrep(q));
  return q->size == 0;
}

/*
 * DESC: Return the element with the most urgent prioritiy of the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  e = pqueue_peek(q);
 * POS: {q --> pqueue}
 */
pqueue_elem pqueue_peek(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));
  pqueue_elem elemento = q->array[pqueue_peek_priority(q)]->elem;
  assert(invrep(q));
  return elemento;
}

/*
 * DESC: Return the priority that is most urgent from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  priority = pqueue_peek_priority(q);
 * POS: {q --> pqueue}
 */
priority_t pqueue_peek_priority(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));
  // comienzo desde el inicio del arreglo a contar todas
  // las posiciones en las que existe una queue
  unsigned int max_priority = 0u;
  for (unsigned int i = q->min_priority; i != 0; i--) {
    // <= porque si max_priority es 5 tengo prioridades 0,1,2,3,4,5, # = 6
    if (q->array[i] != NULL) {
      max_priority = i;
    }
  }
  assert(invrep(q));
  return max_priority;
}

/*
 * DESC: Return the number of elements inside the pqueue 'q'
 *
 */
size_t pqueue_size(pqueue q) {
  assert(invrep(q));
  return q->size;
}

/*
 * DESC: Remove the element with the most urgent priority of the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  q = pqueue_dequeue(q);
 * POS: {q --> pqueue}
 *
 */
pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));
  node_t killme = q->array[pqueue_peek_priority(q)];
  q->array[pqueue_peek_priority(q)] = q->array[pqueue_peek_priority(q)]->next;
  destroy_node(killme);
  q->size--;
  assert(invrep(q));
  return q;
}

/*
 * DESC: Destroy instance of pqueue, freeing all memory used by 'q'.
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_destroy(q);
 * POS: {q == NULL}
 *
 */
pqueue pqueue_destroy(pqueue q) {
  assert(invrep(q));
  while (!pqueue_is_empty(q)) {
    q = pqueue_dequeue(q);
  }
  free(q->array);
  q->array = NULL;
  free(q);
  q = NULL;
  assert(q == NULL);
  return q;
}
