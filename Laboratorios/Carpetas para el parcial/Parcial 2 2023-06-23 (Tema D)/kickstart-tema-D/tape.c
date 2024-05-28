#include "tape.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// node_t apunta a este struct
struct _s_node {
  tape_elem elem;
  struct _s_node *next;
};

// node_t
typedef struct _s_node *node_t;

// s_tape, struct principal del TAD
struct _s_tape {
  unsigned int size;
  node_t cursor; // Puntero al elemento actual
  node_t start;  // Puntero al primer nodo de la cinta
};

// invariante de representacion
static bool invrep(tape_t tape) {
  bool b = false;
  if (tape != NULL) {
    b = true;
  } else if (tape_length(tape) == 0) {
    b = tape->cursor == NULL && tape->start == NULL;
  }
  return b;
}

// crear un nodo
static node_t create_node(tape_elem e) { // ALOCA MEMORIA
  node_t node = malloc(sizeof(*node));
  node->elem = e;
  node->next = NULL;
  return node;
}

static node_t destroy_node(node_t node) { // LIBERA MEMORIA
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

/*
 * Creates a new instance of tape
 *
 * PRE: {true}
 *   tape = tape_create()
 * POST: {tape --> tape_t && tape_at_start(tape) && tape_is_empty(tape)}
 *
 */
tape_t tape_create(void) {
  tape_t tape = malloc(sizeof(*tape));
  tape->cursor = NULL;
  tape->start = NULL;
  tape->size = 0;
  assert(invrep(tape));
  assert(tape_is_empty(tape));
  assert(tape_at_start(tape));
  return tape;
}

/*
 * Set the cursor on the first element of the tape
 *
 * PRE: {tape --> tape}
 *  tape = tape_rewind(tape);
 * POST: {tape --> tape_t && tape_at_start(tape)}
 *
 */
tape_t tape_rewind(tape_t tape) {
  assert(invrep(tape));
  tape->cursor = tape->start;
  assert(invrep(tape));
  assert(tape_at_start(tape));
  return tape;
}

/*
 *
 * Indicates if the cursor of tape <tape> it's pointing to the first element
 *
 */
bool tape_at_start(tape_t tape) { return tape->cursor == tape->start; }

/*
 * Indicates if the cursor of tape <tape> falls out the last element
 *
 */
bool tape_at_stop(tape_t tape) { return tape->cursor == NULL; }

/*
 * Indicates if the tape <tape> has no elements inside
 *
 */
bool tape_is_empty(tape_t tape) { return tape->size == 0u; }

/*
 * Returns how many elements are in the tape
 *
 */
unsigned int tape_length(tape_t tape) { return tape->size; }

/*
 * Moves the cursor one element ahead or stays in the same position if is
 * already in the stop of tape. If the tape's cursor is on the last element,
 * after the call to this function `tape_at_stop(tape)` will return `true`.
 *
 */
tape_t tape_step(tape_t tape) {
  if (tape_at_stop(tape)) {
    // skip
  } else if (!tape_at_stop(tape)) {
    tape->cursor = tape->cursor->next;
  }
  return tape;
}

/*
 * Inserts element <e> in the current position, before the actual element
 *
 * PRE: {tape --> tape_t}
 *   tape = tape_insert(t, e)
 * POST: {tape --> tape_t && !tape_is_empty(tape) && !tape_at_stop(tape) && e ==
 * tape_read(tape)}
 */
tape_t tape_insertl(tape_t tape, tape_elem e) {
  assert(invrep(tape));

  node_t node = create_node(e);

  if (tape_is_empty(tape)) {
    tape->cursor = node;
    tape->start = node;
  } else if (!tape_is_empty(tape)) {
    if (tape_at_start(tape)) {
      node->next = tape->cursor;
      tape->cursor = node;
      tape->start = node;
    } else if (!tape_at_start(tape)) {
      node_t p = tape->start;
      while (p->next != tape->cursor) {
        p = p->next;
      } // p->next == tape->cursor
      p->next = node;
      node->next = tape->cursor;
      tape->cursor = node;
    }
  }

  tape->size = tape->size + 1;
  return tape;
  assert(invrep(tape));
  assert(!tape_is_empty(tape));
  assert(!tape_at_stop(tape));
  assert(e == tape_read(tape));
}

/*
 * Inserts element <e> after the actual element
 *
 * PRE: {tape --> tape_t && (!tape_at_stop(tape) || tape_is_empty(tape))}
 *   tape = tape_insert(t, e)
 *
 * POST: {tape --> tape_t && !tape_is_empty(tape) && !tape_at_end(tape) && e ==
 * tape_read(tape)}
 */
tape_t tape_insertr(tape_t tape, tape_elem e) {
  assert(invrep(tape) && (!tape_at_stop(tape) || tape_is_empty(tape)));
  node_t new_node = create_node(e);
  if (tape->start != NULL) {
    new_node->next = tape->cursor->next;
    tape->cursor->next = new_node;
    tape->cursor = new_node;
  } else {
    tape->start = new_node;
    tape->cursor = new_node;
  }
  tape->size++;
  assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) &&
         e == tape_read(tape));
  return tape;
}

/*
 * Erase the element in the current position
 *
 * PRE: {tape --> tape_t && !tape_is_empty(tape) && !tape_at_stop(tape)}
 *   tape = tape_erase(tape);
 * POST: {tape --> tape_t}
 *
 */
tape_t tape_erase(tape_t tape) {
  assert(invrep(tape));
  assert(!tape_is_empty(tape));
  assert(!tape_at_stop(tape));

  node_t p = tape->start;

  if (tape_at_start(tape)) {
    tape->start = tape->cursor->next;
    tape->cursor = tape->cursor->next;
    destroy_node(p);
  } else if (!tape_at_start(tape)) {
    while (p->next != tape->cursor) {
      p = p->next;
    } // p->next == tape->cursor
    p->next = tape->cursor->next;
    destroy_node(tape->cursor);
    tape->cursor = p->next;
  }

  tape->size = tape->size - 1;

  assert(invrep(tape));
  return tape;
}

/*
 * Returns the current element pointed by the cursor
 *
 * PRE: {tape --> tape_t && !tape_is_empty(tape) && !tape_at_end(tape)}
 *
 */
tape_elem tape_read(tape_t tape) {
  assert(invrep(tape));
  assert(!tape_is_empty(tape));
  assert(!tape_at_stop(tape));
  return tape->cursor->elem;
}

/*
 * Prints the tape on the screen
 *
 */
void tape_dump(tape_t tape) {
  assert(invrep(tape));
  node_t node = tape->start;
  printf("#");
  while (node != NULL) {
    if (node != tape->cursor) {
      printf("-%c-", node->elem);
    } else {
      printf("-[%c]-", node->elem);
    }
    node = node->next;
  }
  if (tape->cursor == NULL) {
    printf("-[]-");
  }
  printf("#\n");
}

/*
 * Creates a copy of <tape> in new memory
 *
 * PRE: {tape --> tape_t}
 *   copy = tape_copy(tape)
 * POS: {copy --> tape_t && copy != tape && tape_at_start(copy) &&
 *       tape_length(tape) == tape_length(copy)}
 *
 */
tape_t tape_copy(tape_t tape) {
  assert(invrep(tape));

  node_t cursor_original = tape->cursor;
  tape = tape_rewind(tape);

  tape_t copy = tape_create();
  while (!tape_at_stop(tape)) {
    copy = tape_insertr(copy, tape_read(tape)); 
    tape = tape_step(tape);
  }

  tape->cursor = cursor_original;
  copy = tape_rewind(copy);

  assert(invrep(tape));
  assert(copy != tape);
  assert(tape_at_start(copy));
  assert(tape_length(tape) == tape_length(copy));
  return tape;
}

/*
 * Destroys the instance freeing all memory used by <tape>
 *
 * PRE: {tape --> tape_t}
 *   tape = tape_destroy(tape);
 * POST: {tape == NULL}
 *
 */
tape_t tape_destroy(tape_t tape) { 
  assert(invrep(tape));
  tape = tape_rewind(tape);
  node_t killme = NULL;
  while (!tape_at_stop(tape)) {
    killme = tape->cursor;
    tape = tape_step(tape);
    destroy_node(killme);
  }
  free(tape);
  tape = NULL;
  assert(tape == NULL);
  return tape;
}
