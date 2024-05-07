#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 4

// -----------------------------------
struct bound_data {
  bool is_upperbound;
  bool is_lowerbound;
  bool exists;
  unsigned int where;
};

void imprimir_bound_data(struct bound_data resultado) {
  printf("Contenido del struct bound_data:\n");
  printf("  Es cota superior: %d.\n", resultado.is_upperbound);
  printf("  Es cota inferior: %d.\n", resultado.is_lowerbound);
  printf("  Existe: %d.\n", resultado.exists);
  if (resultado.exists) {
    printf("  Posicion: %d.\n", resultado.where);
  } else {
    printf("  Posicion: - (no existe).\n");
  }
}

struct from_array {
  int min;
  int max;
  bool exists;
  unsigned int position;
};
// -----------------------------------

void pedir_arreglo(int a[], int n_maximo) {
  int i = 0;
  while (i < n_maximo) {
    printf("Ingrese el elemento %d del arreglo: ", i + 1);
    scanf("%d", &a[i]);
    i = i + 1;
  }
}

void imprime_arreglo(int a[], int n_maximo) {
  int i = 0;
  printf("El arreglo tiene la forma: [");
  while (i < n_maximo) {
    printf("%d", a[i]);
    if (i != n_maximo - 1) {
      printf(", ");
    }
    i = i + 1;
  }
  printf("]\n");
}

int pedir_entero() {
  int n;
  printf("Por favor, dame un entero.\n");
  scanf("%d", &n);
  return n;
}
// -----------------------------------

struct from_array find_from_array(int value, int array[], unsigned int length) {
  unsigned int i = 0;
  struct from_array array_data = {false, false, false, 0};

  array_data.min = INT_MAX;
  array_data.max = INT_MIN;

  while (i < length) {
    // veo si el value es <= al minimo del arreglo
    if (array[i] <= array_data.min)
      array_data.min = array[i];
    // veo si el value es >= al maximo del arreglo
    if (array[i] >= array_data.max)
      array_data.max = array[i];
    // veo si el value es == a algun elemento del arreglo
    if (value == array[i]) {
      array_data.exists = true;
      array_data.position = i;
    }
    i = i + 1;
  }
  return array_data;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
  struct bound_data res = {false, false, false, 0};

  if (value >= find_from_array(value, arr, length).max) {
    res.is_upperbound = true;
  };

  if (value <= find_from_array(value, arr, length).min) {
    res.is_lowerbound = true;
  };

  res.exists = find_from_array(value, arr, length).exists;
  res.where = find_from_array(value, arr, length).position;

  return res;
}

int main(void) {
  int arreglo[ARRAY_SIZE];

  pedir_arreglo(arreglo, ARRAY_SIZE);
  imprime_arreglo(arreglo, ARRAY_SIZE);

  int value = pedir_entero();

  imprimir_bound_data(check_bound(value, arreglo, ARRAY_SIZE));

  return EXIT_SUCCESS;
}
