// /* First, the standard lib includes, alphabetically ordered */
// #include <assert.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>

// /* Then, this project's includes, alphabetically ordered */
// #include "queue.h"
// #include "queue_helpers.h"

// void print_help(char *program_name) {
//   /* Print the usage help of this program. */
//   printf("Usage: %s <input file path>\n\n"
//          "Loads a queue given in a file in disk and prints it on the screen."
//          "\n\n"
//          "The input file must have the following format:\n"
//          " * The first line must contain the string \"empty: \" followed by a
//          " "number" " that indicates with 0 that the content of the file is
//          NOT EMPTY, and" " any other value indicates that there is no data in
//          the file.\n" " * The second line must contain the members of the
//          queue" " separated by one or more spaces. Each member must be an
//          integer."
//          "\n\n"
//          "In other words, the file format is:\n"
//          "empty: <empty_flag>\n"
//          "<elem 1> <elem 2> ... <elem N>\n\n",
//          program_name);
// }

// char *parse_filepath(int argc, char *argv[]) {
//   /* Parse the filepath given by command line argument. */
//   char *result = NULL;
//   // Program takes exactly two arguments
//   // (the program's name itself and the input-filepath)
//   bool valid_args_count = (argc == 2);

//   if (!valid_args_count) {
//     print_help(argv[0]);
//     exit(EXIT_FAILURE);
//   }

//   result = argv[1];

//   return result;
// }

// int main(int argc, char *argv[]) {
//   char *filepath = NULL;

//   /* parse the filepath given in command line arguments */
//   filepath = parse_filepath(argc, argv);

//   // parse the file and returns the loaded queue
//   queue q = queue_from_file(filepath); // NOTE ALLOCATES MEMORY

//   /*dumping the queue */
//   printf("length: %u\n", queue_size(q));
//   queue_dump(q, stdout);

//   queue_destroy(q); // NOTE FREES MEMORY
//   return EXIT_SUCCESS;
// }

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Then, this project's includes, alphabetically ordered */
#include "queue.h"
#include "queue_helpers.h"

void print_help(char *program_name) {
  /* Print the usage help of this program. */
  printf("Usage: %s <input file path>\n\n"
         "Loads a queue given in a file in disk and prints it on the screen."
         "\n\n"
         "The input file must have the following format:\n"
         " * The first line must contain the string \"empty: \" followed by a "
         "number"
         " that indicates with 0 that the content of the file is NOT EMPTY, and"
         " any other value indicates that there is no data in the file.\n"
         " * The second line must contain the members of the queue"
         " separated by one or more spaces. Each member must be an integer."
         "\n\n"
         "In other words, the file format is:\n"
         "empty: <empty_flag>\n"
         "<elem 1> <elem 2> ... <elem N>\n\n",
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

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  // parse the file and returns the loaded queue
  // queue q=queue_from_file(filepath);

  // /*dumping the queue */
  // printf("length: %u\n", queue_size(q));
  // queue_dump(q, stdout);

  /*TODO: BORRAR*/
  /* enable statistics for cpu utilization */
  {
    clock_t start, end;

    start = clock();

    // parse the file and returns the loaded queue
    queue q = queue_from_file(filepath);

    /*dumping the queue */
    printf("length: %u\n", queue_size(q));
    queue_dump(q, stdout);

    q = queue_destroy(q);

    end = clock();

    /* cpu_time used to sort the array */
    double used_cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    /* show the cpu time in seconds used to sort the array */
    printf("\ncpu time used to sort the array: %f seconds.\n", used_cpu_time);
  }

  return EXIT_SUCCESS;
}

/*

La diferencia en tiempo de ejecucion es abismal.

para c-constant, donde las operaciones queue_enqueue() como queue_dequeue() son
O(1) tenemos: unsorted-100000.in -> cpu time used to sort the array: 0.025206
seconds. unsorted-200000.in -> cpu time used to sort the array: 0.049745
seconds.


para a-sizeO1, donde queue_enqueue() es O(n)
unsorted-100000.in -> cpu time used to sort the array: 8.915813 seconds.
unsorted-200000.in -> cpu time used to sort the array: 40.856393 seconds.

*/
