#include "ansicolors.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1820

size_t string_length(const char *str) {
  size_t size = 0;
  for (unsigned i = 0; str[i] != '\0'; i++) {
    size++;
  }
  return size;
}

char *string_clone(const char *str,
                   size_t length) { // debo reservar memoria, sino accedo a
                                    // memoria que no se me permitio acceder
  // char clon[MAX_LENGTH];
  // char *output = clon;
  char *output = malloc(sizeof(char) * length + 1);
  for (size_t i = 0; i < length; i++) {
    output[i] = str[i];
  }
  output[length] = '\0';
  return output;
}

int main(void) {
  // char original[] =
  char *original =
      ""
      "______ time ago in a galaxy far, far away...\n\n\n" ANSI_BRGOLD
      "         _______..___________.     ___      .______             \n"
      "        /       ||           |    /   \\     |   _  \\          \n"
      "       |   (----``---|  |----`   /  ^  \\    |  |_)  |          \n"
      "        \\   \\        |  |       /  /_\\  \\   |      /        \n"
      "    .----)   |       |  |      /  _____  \\  |  |\\  \\----.    \n"
      "    |_______/        |__|     /__/     \\__\\ | _| `._____|     \n"
      "                                                                \n"
      "____    __    ____      ___      .______           _______.     \n"
      "\\   \\  /  \\  /   /     /   \\     |   _  \\         /       |\n"
      " \\   \\/    \\/   /     /  ^  \\    |  |_)  |       |   (----` \n"
      "  \\            /     /  /_\\  \\   |      /         \\   \\    \n"
      "   \\    /\\    /     /  _____  \\  |  |\\  \\----..----)   |   \n"
      "    \\__/  \\__/     /__/     \\__\\ | _| `._____||_______/     \n"
      "\n\n\n"
      "                           Episode II \n\n"
      "                      ATTACK OF THE CLONES\n\n"
      "                There is  unrest in the Galactic\n"
      "                Senate. Several  thousand  solar\n"
      "                systems  have   declared   their\n"
      "                intentions to leave the Republic.\n\n"
      "                This      separatist     movement,\n"
      "                under  the   leadership   of  the\n"
      "                mysterious   Count   Dooku,   has\n"
      "                made it difficult for the limited\n"
      "                number   of   Jedi   Knights   to\n"
      "                maintain   peace   and  order  in\n"
      "                the galaxy.\n\n"
      "                Senator   Amidala,   the   former\n"
      "                Queen   of  Naboo,  is  returning\n"
      "                to  the  Galactic  Senate to vote\n"
      "                on the critical issue of creating\n"
      "                an    ARMY    OF   THE   REPUBLIC\n"
      "                to    assist    the   overwhelmed\n"
      "                Jedi....\n" ANSI_WHITE;
  char *copy = NULL;

  // OPCION 1: // NO ANDA
  /*
      clone_ptr.c: In function ‘main’:
      clone_ptr.c:71:50: warning: division ‘sizeof (char *) / sizeof (char)’
      does not compute the number of array elements [-Wsizeof-pointer-div]
      71 | copy = string_clone(original, sizeof(original) / sizeof(*original));
         |                                                ^
      clone_ptr.c:31:9: note: first ‘sizeof’ operand was declared here
      31 | char *original =
         |         ^~~~~~~~
  */
  // copy = string_clone(original, sizeof(original) / sizeof(*original));
  // yo podria hacer esto
  // assert(sizeof(original) == 8 && sizeof(*original) == 1);

  // OPCION 2: // ANDA
  // copy = string_clone(original, sizeof(char) * string_length(original));
  // 1 * n == n
  // ===
  // sizeof(char) * string_length(original) = string_length(original)

  // OPCION 3: // ANDA
  // copy = string_clone(original, string_length(original) / sizeof(*original));
  // n / 1 == n
  // ===
  // string_length(original) / sizeof(*original) == string_length(original)

  // OPCION 4: // ANDA _ la mejor
  copy = string_clone(original, string_length(original));
  // Entiendo que la OPCION 1 no anda porque
  // sizeof(original) == 4 u 8 (es el tamaño del puntero en si), 8 en mi PC
  // porque es de x64 bits
  // sizeof(*original) == 1, entonces no estoy tomando el largo total, sino
  // 8 solamente. Por eso al ejecutar el programa ignorando la warning
  // imprime Copia   : A long t <-- Estos son 8 caracteres (bytes).
  printf("Original:\n" ANSI_CYAN " %s\n", original);
  copy[0] = 'A';
  copy[1] = ' ';
  copy[2] = 'l';
  copy[3] = 'o';
  copy[4] = 'n';
  copy[5] = 'g';
  printf("Copia   :\n" ANSI_CYAN " %s\n", copy);

  free(copy);

  return EXIT_SUCCESS;
}

// no se que hice, simplemente le di el espacio suficiente (length + 1, 1 para
// el '\0') y se soluciono. Supongo que el problema era acceder afuera de lo que
// me dio el SO
