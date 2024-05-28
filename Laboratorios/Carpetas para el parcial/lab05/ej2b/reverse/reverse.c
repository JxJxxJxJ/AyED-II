/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "../stack.h"
#include "array_helpers.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100u;

void print_help(char *program_name) {
  /* Print the usage help of this program. */
  printf("Usage: %s <input file path>\n\n"
         "Sort an array given in a file in disk.\n"
         "\n"
         "The input file must have the following format:\n"
         " * The first line must contain only a positive integer,"
         " which is the length of the array.\n"
         " * The second line must contain the members of the array"
         " separated by one or more spaces. Each member must be an integer."
         "\n\n"
         "In other words, the file format is:\n"
         "<amount of array elements>\n"
         "<array elem 1> <array elem 2> ... <array elem N>\n\n",
         program_name);
}

char *parse_filepath(int argc, char *argv[]) {
  /* Parse the filepath given by command line argument. */
  char *result = NULL;

  if (argc < 2) {
    print_help(argv[0]);
    exit(EXIT_FAILURE);
  }

  result = argv[1];

  return (result);
}

// int *reverse_array_using_stack(int *array, unsigned int length) {
//   int *new_array;

//   stack s = stack_empty();          // ALLOCATES MEMORY
//   stack s_reversed = stack_empty(); // ALLOCATES MEMORY

//   for (unsigned int i = 0; i < length; i++) {
//     int elem = array[i];
//     s = stack_push(s, elem);
//   }

//   for (unsigned int i = 0; i < length; i++) {
//     int elem = stack_top(s);
//     s_reversed = stack_push(s_reversed, elem);
//     s = stack_pop(s);
//   }

//   new_array = stack_to_array(s_reversed);

//   s = stack_destroy(s);                   // FREES MEMORY
//   s_reversed = stack_destroy(s_reversed); // FREES MEMORY

//   return new_array;
// }

int *reverse_array_using_stack(int *array, unsigned int length) { // NOTE NEW
  int *new_array = malloc(sizeof(*new_array) * length);
  stack s = stack_empty(); // 1. Crear una pila vacia

  for (unsigned int i = 0; i < length; i++) { // 2. Iterar de iz a derecha
    s = stack_push(s, array[i]);              // poniendo los elementos del
  }                                           // arreglo en el stack

  for (unsigned int i = 0; i < length; i++) { // Pongo los elementos en el nuevo
    new_array[i] = stack_top(s);              // arreglo, terminan estando inver
    s = stack_pop(s);                         // tidos
  }

  s = stack_destroy(s);
  return new_array; // new_array lives on the heap
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  /* create an array of MAX_SIZE elements */
  int array[MAX_SIZE];

  /* parse the file to fill the array and obtain the actual length */
  unsigned int length = array_from_file(array, MAX_SIZE, filepath);
  printf("Original: ");
  array_dump(array, length);

  int *new_array = NULL;

  // TODO ------------------------------------- WORKS
  new_array = reverse_array_using_stack(
      array, length); // allocates memory for array (***)
  // ------------------------------------------

  printf("Reversed: ");
  array_dump(new_array, length);

  free(new_array); // frees memory of array (***)
  return (EXIT_SUCCESS);
}
