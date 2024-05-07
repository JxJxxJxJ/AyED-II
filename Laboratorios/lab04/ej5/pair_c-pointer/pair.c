#include "pair.h"
#include "stdlib.h"

pair_t pair_new(int x, int y) {
  pair_t p = NULL;
  p = malloc(sizeof(pair_t));

  p->fst = x; // == (*p).fst = x
  p->snd = y; // == (*p).snd = y
  return p;
}

int pair_first(pair_t p) { return p->fst; }

int pair_second(pair_t p) { return p->snd; }

pair_t pair_swapped(pair_t p) {
  pair_t new_p;
  new_p = pair_new(pair_second(p), pair_first(p));
  return new_p;
}
pair_t pair_destroy(pair_t p) {
  free(p);
  p = NULL;
  return p;
}
