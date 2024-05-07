#include "array_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int data_from_file(const char *path, unsigned int *indexes,
                            char *letters, unsigned int max_size) {

  FILE *file = NULL;
  file = fopen(path, "r");

  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int index;
  char letter;
  unsigned int elements_total = 0;

  unsigned int i = 0u;
  while (i < max_size - 1 && feof(file) == 0) {
    if (2 == fscanf(file, "%u -> *%c*\n", &index, &letter)) {
      indexes[i] = index;
      letters[i] = letter;
      i++;
    } else {
      fprintf(stderr, "Error reading the contents of the file. Make sure the "
                      "format is correct.\n");
      exit(EXIT_FAILURE);
    };
  };

  elements_total = i;

  indexes[i] = '\0';
  letters[i] = '\0';

  fclose(file);
  return elements_total;
}

void array_rebuild(char sorted[], unsigned int indexes[], char *letters,
                   unsigned int length) {
  for (unsigned int i = 0u; i < length; i++) {
    sorted[indexes[i]] = letters[i];
  };
}
