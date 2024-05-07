#include "array_helpers.h"
#include "stdbool.h"
/* First, the standard lib includes, alphabetically ordered */
// #include <assert.h>
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
    return 1;
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
    return 1;
  }

  int f_array_length;
  if (fscanf(fh_input, "%d", &f_array_length) ==
      EOF) { // Here I also read for the first time the file, so it takes the
             // first number on the first line as input
    printf("Error reading the first number from the file, EOF reached before "
           "any number.\n");
    fclose(fh_input);
    return 1;
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

bool array_is_sorted(int a[], unsigned int length) {

  unsigned int i = 0;
  bool sorted = true;

  while (i + 1 < length) {
    sorted = sorted && a[i] <= a[i + 1];

    // if (sorted == false) { // if I wanted to see where the array is unordered
    //   // I'd use this
    //   printf("El arreglo esta desordenado. No sucede que a[%d] = %d < a[%d] "
    //          "=%d. \n ",
    //          i, a[i], i + 1, a[i + 1]);
    //   break;
    // }

    i++;
  }

  // if (sorted) { // It's best to print stuff in main, this function just
  // calculates the boolean `sorted`.
  //   printf("El arreglo esta ordenadisimo.\n");
  // } else
  //   printf("Mmm, falta ordenar el arreglo.\n");

  return sorted;
}

// swaps the elements of two indexes of the array
// a[i] a[j] -> a[j] a[i]
void array_swap(int a[], unsigned int i, unsigned int j) {
  // this doesnt take into account the length of the array, so the indexes
  // might be out of bounds...
  int i_temp = a[i];
  a[i] = a[j];
  a[j] = i_temp;
}

void array_reverse(int a[], unsigned int length) {
  int i = 0;
  int j = length - 1;

  // length = 5
  // length mod 2 == 1          i j
  // _5_ 4  3   2  1 _0_ , swap 0 5     <- (i - j) == -5
  // 0  _4_ 3   2 _1_ 5  , swap 1 4     <- (i - j) == -3
  // 0   1 _3_ _2_ 4  5  , swap 2 3     <- (i - j) == -1
  // 0   1  2   3  4  5  , reversed

  // length = 4
  // length mod 2 == 0          i j
  // _1_  2  3  4  _5_   , swap 0 4     <- (i - j) == -4
  //  5  _2_ 3 _4_  1    , swap 1 3     <- (i - j) == -2
  //  5   2 _3_ 4   1    , swap 2 2     <- (i - j) ==  0    <- (***)
  //  5   4  3  2   1    , reversed

  //  IDEA
  //  while (i - j <= 0){swap(a,i,j); i++; j--}.
  //  Since (i - j <= 0) === (i <= j) then

  //------------------ WAY NUMBER 1 -------------------------------
  // while (i - j <= 0) { // or (i <= j)
  //   array_swap(a, i, j);
  //   i++;
  //   j--;
  // }
  //---------------------------------------------------------------

  // Note how the step (***) doesn't do anything really. I could ignore it
  // and say something like this

  // length = 4
  // length mod 2 == 0          i j
  // _1_  2  3  4  _5_   , swap 0 4     <- (i - j) == -4
  //  5  _2_ 3 _4_  1    , swap 1 3     <- (i - j) == -2
  //  5   2  3  4   1    , reversed

  // In this way (i - j < 0) instead of (i - j <= 0). So the idea becomes
  //  while (i - j < 0){swap(a,i,j); i++; j--}
  //  and since (i - j < 0) === (i < j), I could also do

  //------------------ WAY NUMBER 2 -------------------------------
  while (i < j) { // or (i - j < 0)
    array_swap(a, i, j);
    i++;
    j--;
  }
  //---------------------------------------------------------------
}
