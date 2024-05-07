#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void absolute(int x, int *y) {
  if (x >= 0) {
    *y = x;
  } else {
    *y = -x;
  }
}

int main(void) {
  int a = -10, res = 0; // No modificar esta declaración
                        // --- No se deben declarar variables nuevas ---
  absolute(a, &res);

  printf("El valor de r es = %d \n", res);
  assert(res >= 0 && (res == a || res == -a));
  return EXIT_SUCCESS;
}

// el parametro *y de absolute es de tipo in, no cambio la direccion, sino el
// elemento accedido. (**)
//
// Los parametros de C parecen ser todos In, porque trabajo con copias. Si
// quiero trabajar con referencias y cambiar variables "usadas" como parametros
// deberia usar punteros, que en las funciones de C parecen seguir siendo In por
// lo dicho en (**) (no cambio las direcciones de los punteros en si, sino los
// elementos acedidos por ellos)
