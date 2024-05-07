#include "pair.h"

pair_t pair_new(int x, int y) {
  pair_t p;
  p.values[0] = x;
  p.values[1] = y;
  return p;
}

int pair_first(pair_t p) { return p.values[0]; }

int pair_second(pair_t p) { return p.values[1]; }

pair_t pair_swapped(pair_t p) {
  pair_t new_p;
  new_p = pair_new(pair_second(p), pair_first(p));
  return new_p;
}

pair_t pair_destroy(pair_t p) {
  // skip
  return p;
}
