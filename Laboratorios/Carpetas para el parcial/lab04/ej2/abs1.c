#include <stdio.h>
#include <stdlib.h>

void absolute(int x, int y) {
  if (x >= 0) {
    y = x;
  } else {
    y = -x;
  }
}

int main(void) {
  int a = -10;
  int res = 0;
  absolute(a, res);

  printf("El valor de r es = %d \n", res);
  return EXIT_SUCCESS;
}
