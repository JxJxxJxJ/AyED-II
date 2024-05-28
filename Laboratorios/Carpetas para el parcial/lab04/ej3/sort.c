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
  result = x->rank <= y->rank;
  // result = (*x).rank <= (*y).rank; // I could just use this, this
  // expression
  //                                  // is equivalent to the one above
  return result;
  return true;
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
      swap(&a[i], &a[j]); // NOTE! Version 1 0.000811 seconds.
      // swap(a, i, j); // NOTE! Version 2 0.000804 seconds.
      i = i + 1;
      j = j - 1;
    };
  };

  swap(&a[ppiv], &a[j]); // NOTE! Version 1 0.000811 seconds.
  // swap(a, ppiv, j); // NOTE! Version 2 0.000804 seconds.
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

// cpu time used to sort the array: 0.001904 seconds. using copies
// cpu time used to sort the array: 0.000613 seconds. using pointers
//
// Los intercambios son mas eficientes porque no hago copies en los swaps,
// directamente swapeo usando las direcciones

// ------------------------------------- Con selection sort -------------

// bool goes_before(player_t x, player_t y) { return (x->rank <= y->rank); }

// bool array_is_sorted(player_t atp[], unsigned int length) {
//   unsigned int i = 1u;
//   while (i < length && goes_before(atp[i - 1u], atp[i])) {
//     i++;
//   }
//   return (i == length);
// }

// static unsigned int min_pos_from_player_atp(player_t atp[], unsigned int i,
//                                             unsigned int length) {
//   unsigned int min_pos = i;
//   for (unsigned int j = i + 1; j < length; ++j) {
//     if (!goes_before(atp[min_pos], atp[j])) {
//       min_pos = j;
//     }
//   }
//   return (min_pos);
// }

// void sort(player_t atp[], unsigned int length) {
//   for (unsigned int i = 0u; i < length; ++i) {
//     unsigned int min_pos = min_pos_from_player_atp(atp, i, length);
//     swap(&atp[i], &atp[min_pos]);
//     // printf("Swapee atp[i] = %p, atp[min_pos] = %p\n", (void *)&atp[i],
//     //        (void *)&atp[min_pos]);
//   }
// }
