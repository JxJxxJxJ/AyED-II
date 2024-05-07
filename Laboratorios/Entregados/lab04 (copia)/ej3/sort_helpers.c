#include "player.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void swap(player_t *p1,   // NOTE! Version 1 0.000811 seconds.
          player_t *p2) { // NOTE! player_t * p == (struct _player_t *) * p
  player_t aux = *p1;     // NOTE! is this too much voodoo for our purposes?
  *p1 = *p2;
  *p2 = aux;
}

// void swap(player_t a[], unsigned int i,
//           unsigned int j) { // NOTE! Version 2 0.000804 seconds.
//   player_t aux;
//   aux = a[i];
//   a[i] = a[j];
//   a[j] = aux;
// }
