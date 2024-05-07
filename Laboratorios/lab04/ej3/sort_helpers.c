#include "player.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void swap(player_t *p1, player_t *p2) {
  player_t aux = *p1;
  *p1 = *p2;
  *p2 = aux;
}
