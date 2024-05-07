#include "sort_helpers.h"

void swap(player_t a[], unsigned int i, unsigned int j) {
  player_t temp_i = a[i];
  a[i] = a[j];
  a[j] = temp_i;
}

// void swap(player_t *a, unsigned int i, unsigned int j) {
//   player_t temp_i = *(a + i);
//   *(a + i) = *(a + j);
//   *(a + j) = temp_i;
// }
