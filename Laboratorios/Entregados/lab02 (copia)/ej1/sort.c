#include "sort.h"
#include "array_helpers.h"
#include "sort_helpers.h"
#include <assert.h>
#include <stdbool.h>

static void insert(int a[], unsigned int i) {
  unsigned int j;
  j = i;
  while (j >= 1 && goes_before(a[j], a[j - 1])) { // (****)
    swap(a, j - 1, j);
    j = j - 1;
  }
}

void insertion_sort(int a[], unsigned int length) {
  for (unsigned int i = 1; i < length; i++) {
    assert(array_is_sorted(a, i)); // checks invariant
    insert(a, i);
  }
}

// (****)
// goes before seems to calculate the ordering based on
// the number's magnitude (at least with numbers)
// goes_before[3,-4] == true
