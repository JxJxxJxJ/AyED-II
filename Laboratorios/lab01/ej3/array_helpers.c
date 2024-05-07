#include "array_helpers.h"

/* First, the standard lib includes, alphabetically ordered */
// #include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_file(int array[], unsigned int max_size,
                             const char *filepath) {
  if (max_size > MAX_SIZE) {
    printf("Error trying to read array from file of length %d which is bigger "
           "than the maximum length given by MAX_SIZE = %d",
           max_size, MAX_SIZE);
    abort();
  }
  // I want to read ../input/*.in using C functions
  // and create an array using the data from the file.

  // I open the file using a file handle
  FILE *fh_input; // this creates a reference to the file named fh_input
  fh_input =
      fopen(filepath,
            "r"); // this opens a file in filepath in "r" mode (read only),

  if (fh_input == NULL) { // if I can't open the file for whatever reason, fopen
                          // will return null and here I handle that error.
    printf("Error opening the file (file handle == NULL)");
    abort();
  }

  int f_array_length;
  if (fscanf(fh_input, "%d", &f_array_length) ==
      EOF) { // Here I also read for the first time the file, so it takes the
             // first number on the first line as input
    printf("Error reading the first number from the file, EOF reached before "
           "any number.\n");
    fclose(fh_input);
    abort();
  }

  // Up to here f_array_length holds the length of the array I want to create.

  int number_counter = 0;
  int number_read_from_fscanf;
  while (fscanf(fh_input, "%d", &number_read_from_fscanf) != EOF &&
         number_counter < f_array_length) { // populates the array with the
                                            // numbers from the second line
    array[number_counter] = number_read_from_fscanf;
    number_counter++;
  }

  // assert(f_array_length == number_counter);
  if (f_array_length != number_counter) {
    printf(
        "La longitud del arreglo es %d, y me diste %d elementos. Abortando.\n",
        f_array_length, number_counter);
    abort();
  };

  fclose(fh_input);      // this closes the file after being done
                         // with it
  return number_counter; // Outputs the number of read numbers
                         // to later print them using array_dump
}

void array_dump(int a[], unsigned int length) {
  // Here I can just print the array a[] of length length
  // with the format specified
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
