#include "array_helpers.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

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

  return result;
}

static void dump(char a[], unsigned int length) {
  printf("\"");
  for (unsigned int j = 0u; j < length; j++) {
    printf("%c", a[j]);
  }
  printf("\"");
  printf("\n\n");
}

int main(int argc, char *argv[]) {
  unsigned int indexes[MAX_SIZE];
  char letters[MAX_SIZE];
  char sorted[MAX_SIZE];
  unsigned int length = 0;
  //  .----------^
  //  :
  // Debe guardarse aqui la cantidad de elementos leidos del archivo

  // read `file/in/filepath` and rebuild the array with "%d -> *%c*\n" in each
  // line, then save it in `sorted`
  char *file = NULL;
  file = parse_filepath(argc, argv);

  length = data_from_file(file, indexes, letters, MAX_SIZE);
  array_rebuild(sorted, indexes, letters, length);

  dump(sorted, length);

  return EXIT_SUCCESS;
}
