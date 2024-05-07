// #include <assert.h>
#include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include "array_helpers.h"
#include "fixstring.h"
#include "sort_helpers.h"

void swap(fixstring a[], unsigned int i, unsigned int j) {
  fstring_swap(a[i], a[j]);
}

bool goes_before_lexicographical(fixstring x, fixstring y) {
  bool result = fstring_less_eq(x, y);
  return result;
}

bool goes_before_length(fixstring x, fixstring y) {
  bool result = (fstring_length(x) <= fstring_length(y));
  return result;
}

bool array_is_sorted_lexicographical(fixstring array[], unsigned int length) {
  unsigned int i = 1;
  while (i < length && goes_before_lexicographical(array[i - 1], array[i])) {
    i++;
  }
  return (i >= length);
}

bool array_is_sorted_length(fixstring array[], unsigned int length) {
  unsigned int i = 1;
  while (i < length && goes_before_length(array[i - 1], array[i])) {
    i++;
  }
  return (i >= length);
}
