#include "array_helpers.h"
#include "mybool.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

unsigned int array_from_file(int array[], unsigned int max_size,
                             const char *filepath) {
  if (max_size > MAX_SIZE) {
    printf("Error trying to read array from file of length %d which is bigger "
           "than the maximum length given by MAX_SIZE = %d",
           max_size, MAX_SIZE);
    return 1;
  }

  FILE *fh_input;
  fh_input = fopen(filepath, "r");

  if (fh_input == NULL) {

    printf("Error opening the file (file handle == NULL)");
    return 1;
  }

  int f_array_length;
  if (fscanf(fh_input, "%d", &f_array_length) == EOF) {

    printf("Error reading the first number from the file, EOF reached before "
           "any number.\n");
    fclose(fh_input);
    return 1;
  }

  int number_counter = 0;
  int number_read_from_fscanf;
  while (fscanf(fh_input, "%d", &number_read_from_fscanf) != EOF &&
         number_counter < f_array_length) {

    array[number_counter] = number_read_from_fscanf;
    number_counter++;
  }

  if (f_array_length != number_counter) {
    printf(
        "La longitud del arreglo es %d, y me diste %d elementos. Abortando.\n",
        f_array_length, number_counter);
    abort();
  };

  fclose(fh_input);

  return number_counter;
}

void array_dump(int a[], unsigned int length) {
  unsigned int i = 0;
  printf("[");
  while (i < length) {
    printf("%d", a[i]);
    if (i != length - 1) {
      printf(", ");
    }
    i = i + 1;
  }
  printf("]\n");
}

mybool array_is_sorted(int a[], unsigned int length) {

  unsigned int i = 0;
  mybool sorted = true;

  while (i + 1 < length) {
    sorted = sorted && a[i] <= a[i + 1];
    i++;
  }

  return sorted;
}
