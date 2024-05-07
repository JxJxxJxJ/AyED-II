/*
  @file sort.c
  @brief sort functions implementation
*/

#include "sort.h"
#include "helpers.h"
#include "player.h"
#include "sort_helpers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool goes_before(player_t x, player_t y) {
  bool result;
  result = x.rank <= y.rank;
  return result;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
  unsigned int i = 1u;
  while (i < length && goes_before(atp[i - 1u], atp[i])) {
    i++;
  }
  return (i == length);
}

static unsigned int partition(player_t a[], unsigned int izq,
                              unsigned int der) {
  unsigned int i;
  unsigned int j;
  unsigned int ppiv;
  ppiv = izq;
  i = izq + 1;
  j = der;

  while (i <= j) {
    if (goes_before(a[i], a[ppiv])) {
      i = i + 1;
    } else if (goes_before(a[ppiv], a[j])) {
      j = j - 1;
    } else if (!goes_before(a[i], a[ppiv]) && !goes_before(a[ppiv], a[j])) {
      swap(a, i, j);
      i = i + 1;
      j = j - 1;
    };
  };

  swap(a, ppiv, j);
  ppiv = j;

  return ppiv;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
  unsigned int ppiv;
  if (der > izq) {
    ppiv = partition(a, izq, der);
    quick_sort_rec(a, izq, (ppiv == 0u) ? 0u : ppiv - 1u);
    quick_sort_rec(a, ppiv + 1, der);
  }
}

void sort(player_t a[], unsigned int length) {
  quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
