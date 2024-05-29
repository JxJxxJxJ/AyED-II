#include "tape.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct _s_node {
  tape_elem elem;
  struct _s_node *next;
};

typedef struct _s_node *node_t;

struct _s_tape {
  unsigned int size;
  node_t cursor; // Puntero al elemento actual
  node_t start;  // Puntero al primer nodo de la cinta
};

static bool invrep(tape_t tape) {
  bool b;
  if (tape != NULL) {
    b = true;
  }

  if (tape->size == 0u) {
    b = tape->cursor == NULL && tape->start == NULL;
  }

  return b;
} // TODO

static node_t create_node(tape_elem e) {
  node_t node = malloc(sizeof(*node));
  node->elem = e;
  node->next = NULL;
  return node;
}

static node_t destroy_node(node_t node) {
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

tape_t tape_create(void) {
  tape_t tape = malloc(sizeof(*tape));
  tape->size = 0u;
  tape->cursor = NULL;
  tape->start = NULL;
  assert(invrep(tape) && tape_is_empty(tape) && tape_at_start(tape));
  return tape;
}

tape_t tape_rewind(tape_t tape) {
  tape->cursor = tape->start;
  return tape;
}

bool tape_at_start(tape_t tape) { return tape->cursor == tape->start; }

bool tape_at_stop(tape_t tape) { return tape->cursor == NULL; }

bool tape_is_empty(tape_t tape) { return tape->size == 0u; }

unsigned int tape_length(tape_t tape) { return tape->size; }

tape_t tape_step(tape_t tape) {
  tape->cursor = tape->cursor->next;
  return tape;
}

tape_t tape_insertl(tape_t tape, tape_elem e) {
  node_t node = create_node(e);
  if (tape_at_start(tape)) {
    tape->start = node;
    node->next = tape->cursor;
  } else {
    node_t p = tape->start;
    while (p->next != tape->cursor) {
      p = p->next;
    }
    p->next = node;
    node->next = tape->cursor;
  }
  tape->size++;
  return tape;
}

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

tape_t tape_erase(tape_t tape) {
  node_t p = tape->start;
  if (tape_at_start(tape)) {
    tape->start = tape->start->next;
    tape->cursor = tape->cursor->next;
    destroy_node(p);
  } else {
    while (p->next != tape->cursor) {
      p = p->next;
    }
    p->next = p->next->next;
    destroy_node(tape->cursor);
    tape->cursor = p->next;
  }
  tape->size--;
  return tape;
}

tape_elem tape_read(tape_t tape) { return tape->cursor->elem; }

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

tape_t tape_copy(tape_t tape) {
  tape_t copy = tape_create();

  node_t cursor_original_tape = tape->cursor;

  tape = tape_rewind(tape);
  while (!tape_at_stop(tape)) {
    tape_insertr(copy, tape->cursor->elem);
    tape = tape_step(tape);
  }

  copy = tape_rewind(copy);
  tape = tape_rewind(tape);
  while (tape->cursor != cursor_original_tape) {
    copy = tape_step(copy);
    tape = tape_step(tape);
  }

  return copy;
}

tape_t tape_destroy(tape_t tape) {

  tape = tape_rewind(tape);
  while (!tape_is_empty(tape)) {
    tape = tape_erase(tape);
  }

  free(tape);
  tape = NULL;
  return tape;
}
