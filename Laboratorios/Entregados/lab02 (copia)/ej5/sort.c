// #include <assert.h>
#include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include "array_helpers.h"
#include "fixstring.h"
#include "sort.h"
#include "sort_helpers.h"

// ------------------------------------------------------------
// QuickSort using goes_before_lexicographical (uses fstring_less_eq)
static unsigned int partition(fixstring a[], unsigned int izq,
                              unsigned int der) {
  unsigned int i;
  unsigned int j;
  unsigned int ppiv;
  ppiv = izq;
  i = izq + 1;
  j = der;

  while (i <= j) {
    if (goes_before_lexicographical(a[i], a[ppiv])) { // ok
      i = i + 1;
    } else if (goes_before_lexicographical(a[ppiv], a[j])) { // ok
      j = j - 1;
    } else if (!goes_before_lexicographical(a[i], a[ppiv]) &&
               !goes_before_lexicographical(a[ppiv], a[j])) {
      swap(a, i, j);
      i = i + 1;
      j = j - 1;
    };
  };

  swap(a, ppiv, j);
  ppiv = j;

  return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
  unsigned int ppiv;
  if (der > izq) {
    ppiv = partition(a, izq, der);
    quick_sort_rec(a, izq, (ppiv == 0u) ? 0u : ppiv - 1u);
    quick_sort_rec(a, ppiv + 1, der);
  }
}

void quick_sort(fixstring a[], unsigned int length) {
  quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
// ------------------------------------------------------------
// QuickSort usign goes_before_length (usa fstring_length <= ...)
static unsigned int partition_length(fixstring a[], unsigned int izq,
                                     unsigned int der) {
  unsigned int i;
  unsigned int j;
  unsigned int ppiv;
  ppiv = izq;
  i = izq + 1;
  j = der;

  while (i <= j) {
    if (goes_before_length(a[i], a[ppiv])) { // ok
      i = i + 1;
    } else if (goes_before_length(a[ppiv], a[j])) { // ok
      j = j - 1;
    } else if (!goes_before_length(a[i], a[ppiv]) &&
               !goes_before_length(a[ppiv], a[j])) {
      swap(a, i, j);
      i = i + 1;
      j = j - 1;
    };
  };

  swap(a, ppiv, j);
  ppiv = j;

  return ppiv;
}

static void quick_sort_rec_length(fixstring a[], unsigned int izq,
                                  unsigned int der) {
  unsigned int ppiv;
  if (der > izq) {
    ppiv = partition_length(a, izq, der);
    quick_sort_rec_length(a, izq, (ppiv == 0u) ? 0u : ppiv - 1u);
    quick_sort_rec_length(a, ppiv + 1, der);
  }
}

void quick_sort_length(fixstring a[], unsigned int length) {
  quick_sort_rec_length(a, 0, (length == 0) ? 0 : length - 1);
}
// ------------------------------------------------------------
