// #include <assert.h>
#include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include "array_helpers.h"
#include "sort.h"
#include "sort_helpers.h"

static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
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

  /* Permutes elements of a[izq..der] and returns pivot such that:
   - izq <= pivot <= der
   - elements in a[izq,pivot) all 'go_before' (according to function
   goes_before) a[pivot]
   - a[pivot] 'goes_before' all the elements in a(pivot,der]
  */

  return ppiv;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
  unsigned int ppiv;
  if (der > izq) {
    ppiv = partition(a, izq, der);
    quick_sort_rec(a, izq, (ppiv == 0u) ? 0u : ppiv - 1u);
    quick_sort_rec(a, ppiv + 1, der);
  }
}

void quick_sort(int a[], unsigned int length) {
  quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
