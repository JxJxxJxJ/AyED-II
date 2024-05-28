#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"

struct _counter {
  unsigned int count;
};

counter counter_init(void) {
  counter p;
  p = malloc(sizeof(counter));
  p->count = 0u;
  return p;
}

void counter_inc(counter c) { c->count++; }

bool counter_is_init(counter c) { return c->count == 0; }

void counter_dec(counter c) {
  assert(!counter_is_init(c)); // precondition
  c->count = c->count - 1;
}

counter counter_copy(counter c) {
  counter copy;
  copy = malloc(sizeof(counter));
  copy->count = c->count;
  return copy;
}

void counter_destroy(counter c) { free(c), c = NULL; }
