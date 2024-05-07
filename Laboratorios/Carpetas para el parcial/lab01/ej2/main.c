/* First, the standard lib includes, alphabetically ordered */
// #include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
  /* Print the usage help of this program. */
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
  /* Parse the filepath given by command line argument. */
  char *result = NULL;
  // Program takes exactly two arguments
  // (the program's name itself and the input-filepath)
  bool valid_args_count = (argc == 2);

  if (!valid_args_count) {
    print_help(argv[0]);
    exit(EXIT_FAILURE);
  }

  result = argv[1];

  return result;
}

unsigned int array_from_file(int array[], unsigned int max_size
                             // , const char *filepath // Lo longer used
) {
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

  // ---------------------
  // instead of opening a file, my file handler is stdin itself
  // fh_input =
  //     fopen(filepath,
  //           "r"); // this opens a file in filepath in "r" mode (read only),
  // ---------------------

  fh_input = stdin;

  // ---------------------
  // stdin starts empty, so I don't need this error handling
  // if (fh_input == NULL) { // if I can't open the file for whatever reason,
  // fopen
  //                         // will return null and here I handle that error.
  //   printf("Error opening the file (file handler == NULL)");
  //   abort();
  // }
  // ---------------------

  int f_array_length; // cannot be unsigned int because if I want to check
                      // whether or not it's negative (as an assert), -Werror
                      // shows me the "unsigned int are always >=0" warning.
                      // Even though fscanf hangs after reading -2 instead of
                      // doing anything.
  fscanf(fh_input, "%d", &f_array_length);

  while (f_array_length < 0) {
    printf("Array length must be a natural number. Please try again.\n");
    fscanf(fh_input, "%d", &f_array_length);
  }

  // Up to here f_array_length holds the length of the array I want to
  // create.

  int position = 0;
  int number_read_from_fscanf;

  while (position < f_array_length) { // populates the array with the numbers
                                      // from the user input
    // fscanf(fh_input, "%d", &number_read_from_fscanf);
    fscanf(fh_input, "%d", &number_read_from_fscanf);
    array[position] = number_read_from_fscanf;
    position++;
  }

  fclose(fh_input); // this closes the file after being done
                    // with it
  return position;  // Outputs the number of read numbers
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

int main() {

  /* create an array of MAX_SIZE elements */
  int array[MAX_SIZE];

  /* parse the file to fill the array and obtain the actual length */
  unsigned int length = array_from_file(
      array, MAX_SIZE /* , filepath */); // Filepath argument no longer used
                                         // since I'm reading from stdin

  /*dumping the array*/
  array_dump(array, length);

  return EXIT_SUCCESS;
}
