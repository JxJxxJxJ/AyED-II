#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct s_queue {
  unsigned int size; // NOTE (**) No deberia ahora
                     // fortalecer la invrep?
                     // (Intento,pero no se me ocurre una forma
                     // que no de stack overflow)

  struct s_node *first;
};

struct s_node {
  queue_elem elem;
  struct s_node *next;
};

static struct s_node *create_node(queue_elem e) {
  struct s_node *new_node = malloc(sizeof(struct s_node));
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

static bool invrep(queue q) {
  return q != NULL && q->size == queue_size(q); // NOTE (***) Me gustaria
  // fortalecer la invariante
  // de
  // representacion con esto
  // pero me da stack
  // overflow..., esta bien no
  // fortalecerla?
}

queue queue_empty(void) { // NOTE ALLOCATES MEMORY
  queue q = malloc(sizeof(*q));
  q->size = 0;
  q->first = NULL;
  assert(invrep(q) && queue_is_empty(q));
  return q;
}

// Agrego un elemento al final de la cola
queue queue_enqueue(queue q, queue_elem e) { // NOTE Must
                                             // preserve q->size
                                             // invariant
  assert(invrep(q));
  struct s_node *new_node = create_node(e);
  new_node->elem = e;    // El nodo
  new_node->next = NULL; // esta al fondo
  if (q->first == NULL) {
    q->first = new_node;
  } else {
    struct s_node *p = q->first;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = new_node;
  }
  q->size++;
  assert(invrep(q) && !queue_is_empty(q));
  return q;
}

bool queue_is_empty(queue q) {
  assert(invrep(q)); // NOTE
  return q->first == NULL;
}

queue_elem queue_first(queue q) {
  assert(invrep(q) && !queue_is_empty(q));
  return q->first->elem;
}

unsigned int queue_size(queue q) {
  // assert(invrep(q)); // NOTE (**) Adds stack overflow
  return q->size;
}

queue queue_dequeue(queue q) { // NOTE Must preserve q->size invariant
  assert(invrep(q) && !queue_is_empty(q));
  struct s_node *killme = q->first;
  q->first = q->first->next;
  killme = destroy_node(killme);
  q->size--;
  assert(invrep(q));
  return q;
}

void queue_dump(queue q, FILE *file) {
  file = file == NULL ? stdout : file;
  struct s_node *node = q->first;
  fprintf(file, "[ ");
  while (node != NULL) {
    fprintf(file, "%d", node->elem);
    node = node->next;
    if (node != NULL) {
      fprintf(file, ", ");
    }
  }
  fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
  assert(invrep(q));
  struct s_node *node = q->first;
  while (node != NULL) {
    struct s_node *killme = node;
    node = node->next;
    killme = destroy_node(killme);
  }
  free(q);
  q = NULL;
  assert(q == NULL);
  return q;
}

queue queue_disscard(queue q, unsigned int n) {
  assert(q != NULL && n < queue_size(q));
  // points to the beginning of the queue
  struct s_node *p = q->first;

  if (n == 0) {
    q->first = q->first->next;
    free(p);
    p = q->first; // me lo deja acomodado
  }

  else if (n > 0) {
    for (unsigned int i = 0; i < n - 1; i++) {
      p = p->next;
    }
    struct s_node *killme = p->next;
    p->next = killme->next;
    free(killme);
  }

  q->size--; // preserves the invariant
  assert(q != NULL);
  return q;
}

/*
*

// caso n = 4
            0        1        2        3        4
           [1| ] -> [2| ] -> [3| ] -> [4| ] -> [5| ] -> NULL
q -> first --^
p -------------------------------------^        ^
killme -----------------------------------------^

*
*/
