#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main() {
  int x = 6;
  int y = 4;

  swap(&x, &y);
  printf("x = %d, y = %d \n", x, y);
  return EXIT_SUCCESS;
}
