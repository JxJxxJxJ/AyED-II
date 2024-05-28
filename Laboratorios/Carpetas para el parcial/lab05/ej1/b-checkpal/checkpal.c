#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

char *destroy(char *s) {
  free(s);
  s = NULL;
  return s;
}

int main(void) {
  char user_input[MAX_LENGTH];
  char ignore_chars[] = {' ', '?', '!', ',', '-', '.', '\n'};
  char *filtered = NULL;

  printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ",
         MAX_LENGTH);
  // scanf("%s", user_input); // Para al primer espacio, uso fgets mejor
  char *res = fgets(user_input, MAX_LENGTH, stdin);
  if (res == NULL) {
    printf("Error reading chars. \n");
    return EXIT_FAILURE;
  }

  filtered = string_filter(user_input, ignore_chars[0]);
  for (unsigned int i = 0; i < SIZEOF_ARRAY(ignore_chars); i++) {
    char *p = filtered;
    filtered = string_filter(filtered, ignore_chars[i]);
    destroy(p);
  }

  printf("El texto:\n\n"
         "\"%s\" \n\n"
         "%s un palíndromo.\n\n",
         filtered, string_is_symmetric(filtered) ? "Es" : "NO es");

  destroy(filtered);
  return EXIT_SUCCESS;
}
