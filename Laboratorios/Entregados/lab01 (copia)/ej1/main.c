#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

void print_help(char *program_name) {
  printf("Usage: %s <input file path>\n\n"
         "Loads an array given in a file in disk and prints it on the screen."
         "\n\n"
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
  char *result = NULL;
  bool valid_args_count = (argc == 2);

  if (!valid_args_count) {
    print_help(argv[0]);
    exit(EXIT_FAILURE);
  }

  result = argv[1];

  return result;
}

unsigned int array_from_file(int array[], unsigned int max_size,
                             const char *filepath) {
  if (max_size > MAX_SIZE) {
    printf("Error trying to read array from file of length %d which is bigger "
           "than the maximum length given by MAX_SIZE = %d",
           max_size, MAX_SIZE);
    abort();
  }

  FILE *fh_input;
  fh_input = fopen(filepath, "r");
  if (fh_input == NULL) {
    printf("Error opening the file (file handle == NULL)");
    abort();
  }

  int f_array_length;
  if (fscanf(fh_input, "%d", &f_array_length) == EOF) {
    printf("Error reading the first number from the file, EOF reached before "
           "any number.\n");
    fclose(fh_input);
    abort();
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

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  filepath = parse_filepath(argc, argv);

  int array[MAX_SIZE];

  unsigned int length = array_from_file(array, 0, filepath);

  array_dump(array, length);

  return EXIT_SUCCESS;
}
