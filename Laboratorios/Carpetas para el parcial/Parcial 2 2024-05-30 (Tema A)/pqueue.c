#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "character/character.h"
#include "pqueue.h"

/* ============================================================================
STRUCTS!
============================================================================ */

typedef struct s_node *node_t;

struct s_pqueue {
  size_t size;
  node_t front;
  // unsigned int highest_priority; // No necesario?
};

struct s_node {
  Character character;
  float priority;
  node_t next;
};
/* ============================================================================
INVREP
============================================================================ */

static bool invrep(pqueue q) {
  bool b = true;

  // si esta vacio o con 1 elemento ya es trivial

  if (q->size >= 2) {
    node_t p = q->front; // comienzo desde el inicio
    while (p->next != NULL) {
      b = p->priority >= p->next->priority;
      p = p->next;
    }
  }

  return b;
}

/* ============================================================================
NEW
============================================================================ */

/*
 * DESC: Creates a new instance of pqueue
 *
 * PRE: {true}
 *  q = pqueue_empty();
 * POS: {q --> pqueue && pqueue_is_empty(q)}
 *
 */
pqueue pqueue_empty(void) {
  pqueue q = malloc(sizeof(*q)); // NOTE ALOCA MEMORIA
  q->front = NULL;
  q->size = 0u;
  // q->highest_priority = 0u;

  assert(invrep(q));
  assert(pqueue_is_empty(q));
  return q;
}

/* ============================================================================
ENQUEUE
============================================================================ */

static float calculate_priority(Character character) {
  float iniciative = 0u; // Valores de 0 a 15

  // Calculo baseInitiative
  unsigned int baseInitiative = character_agility(character);

  // Calculo modificador
  float modificador = 0;
  if (character_ctype(character) == agile) {
    modificador = 1.5; // 150%
  }

  else if (character_ctype(character) == tank) {
    modificador = 0.8; // 80%
  }

  else
    modificador = 1.0; // 100%

  // Calculo isAlive
  float isAlive = 0.0;
  if (character_is_alive(character)) {
    isAlive = 1.0;
  } else
    isAlive = 0.0;

  iniciative = (float)baseInitiative * modificador * isAlive;
  // character_print(character);
  // printf(" Iniciative calcualda es %f\n", iniciative);
  return iniciative;
}

static struct s_node *create_node(Character character) { // NOTE ALOCA MEMORIA
  struct s_node *new_node = NULL;
  new_node = malloc(sizeof(struct s_node));
  assert(new_node != NULL);
  new_node->character = character;
  new_node->priority = calculate_priority(character);
  new_node->next = NULL;
  return new_node;
}

/*
 * DESC: Adds a character 'character' into the pqueue 'q'
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_enqueue(q, character);
 * POS: {q --> pqueue && !pqueue_is_empty()}
 *
 */
pqueue pqueue_enqueue(pqueue q, Character character) {
  assert(invrep(q));
  struct s_node *new_node = create_node(character);
  new_node->priority = calculate_priority(character);

  if (pqueue_is_empty(q)) { // Si la pqueue esta vacia, lo pongo directamente
                            // actualizando los campos
    q->front = new_node;
    // q->highest_priority = new_node->priority;
  }

  else {
    // Coloco el nodo, si la prioridad es <= lo pongo mas al fondo
    if (pqueue_size(q) == 1) {
      if (q->front->priority < new_node->priority) { // Lo pongo antes,
        new_node->next = q->front;
        q->front = new_node;
        // q->highest_priority = new_node->priority; // hay un elemento nuevo
        // con
        //  mayor prioridad
      } else if (q->front->priority >= new_node->priority) { // Lo pongo despues
        q->front->next = new_node;
        // y no actualizo prioridad maxima
      }
    }

    else if (pqueue_size(q) >= 2) {
      // (!pqueue_is_empty(q))
      // Lo debo insertar segun su prioridad
      node_t p = q->front;
      while (p->next != NULL && p->next->priority >= new_node->priority) {
        p = p->next;
      } // p -> next apunta al primer personaje con prioridad < a c_priority
      new_node->next = p->next;
      p->next = new_node;
    }
  }
  q->size = q->size + 1; // Aumento en 1 el size tras encolar
  assert(invrep(q));
  assert(!pqueue_is_empty(q));
  return q;
}

/* ============================================================================
IS EMPTY?
============================================================================ */
/*
 * DESC: Indicates whether the pqueue 'q' is empty or not
 *
 * PRE: {q --> pqueue}
 *  empty = pqueue_is_empty(q);
 * POS: {q --> pqueue}
 *
 */
bool pqueue_is_empty(pqueue q) {
  assert(invrep(q));
  bool b = q->size == 0u;
  assert(invrep(q));
  return b;
}

/* ============================================================================
PEEKS
============================================================================ */
/*
 * DESC: Returns the character with the highest priority from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  character = pqueue_peek(q);
 * POS: {q --> pqueue}
 *
 */
Character pqueue_peek(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));

  Character c_highest_priority =
      q->front->character; // Como ya esta ordenada de mayor prioridad a menor,
                           // el primero es el de mayor prioridad

  assert(invrep(q));
  return c_highest_priority;
}

/*
 * DESC: Returns the priority of the character with the highest priority from
 * the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  priority = pqueue_peek_priority(q);
 * POS: {q --> pqueue}
 */
float pqueue_peek_priority(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));

  float highest_priority = q->front->priority; // O(1)

  assert(invrep(q));
  return highest_priority;
}

/* ============================================================================
SIZE
============================================================================ */
/*
 * DESC: Returns the number of elements inside the pqueue 'q'
 *
 * PRE: {q --> pqueue}
 *  size = pqueue_size(q);
 * POS: {q --> pqueue}
 *
 */
unsigned int pqueue_size(pqueue q) {
  assert(invrep(q));
  unsigned int size = q->size; // O(1)
  assert(invrep(q));
  return size;
}

/* ============================================================================
COPY
============================================================================ */
/*
 * DESC: Returns a copy of the pqueue 'q'
 *
 * PRE: {q --> pqueue}
 *  copy = pqueue_copy(q);
 * POS: {q --> pqueue && copy --> pqueue}
 *
 */
pqueue pqueue_copy(pqueue q) {
  assert(invrep(q));

  pqueue copy = pqueue_empty(); // NOTE ALOCA MEMORIA
  node_t p = q->front;

  while (p != NULL) { // Recorro uno por uno en q y los encolo en copy
    Character c_copy = character_copy(p->character);
    copy = pqueue_enqueue(copy, c_copy);
    p = p->next;
  }

  assert(invrep(q));
  assert(invrep(copy));
  return copy;
}

/* ============================================================================
DESTROY!
============================================================================ */
static struct s_node *destroy_node(struct s_node *node) { // NOTE libera memoria
  assert(node != NULL);
  node->next = NULL;
  free(node);
  node = NULL;
  assert(node == NULL);
  return node;
}

/*
 * DESC: Removes the character with the highest priority from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  q = pqueue_dequeue(q);
 * POS: {q --> pqueue}
 *
 */
pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));
  node_t p = q->front;
  q->front = q->front->next;
  character_destroy(p->character);
  p = destroy_node(p);
  q->size = q->size - 1;
  assert(invrep(q));
  return q;
}

/*
 * DESC: Destroys the instance of pqueue, freeing all memory used by 'q'
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
  free(q);
  q = NULL;
  assert(q == NULL);
  return q;
}
