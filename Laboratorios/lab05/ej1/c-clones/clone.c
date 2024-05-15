#include "ansicolors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1820

char *string_clone(const char *str, size_t length) {
  // char clon[MAX_LENGTH]; // Es una variable local que vive en el stack
  // char *output = clon;   // Apunta a una variable del stack
  // FIX DOWN BELOW
  // Now outputs points to the heap
  char *output = malloc(sizeof(*output) * length + 1);
  for (size_t i = 0; i < length; i++) {
    output[i] = str[i];
  }
  output[length] = '\0';
  return output; // Output points to an address in the heap
}

int main(void) {
  char original[] =
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
  copy = string_clone(original,
                      sizeof(original) / sizeof(*original)); // ALLOCATES MEMORY
  // Como original es un arreglo estatico (l:22) entonces sizeof(original) me da
  // la longitud del arreglo, si divido por sizeof(*original) entonces divido
  // por el peso de cada caracter, me da 1812 / 1 bytes = 1812bytes

  printf("Original:\n" ANSI_CYAN " %s\n", original);
  copy[0] = 'A';
  copy[1] = ' ';
  copy[2] = 'l';
  copy[3] = 'o';
  copy[4] = 'n';
  copy[5] = 'g';
  printf("Copia   :\n" ANSI_CYAN " %s\n", copy);

  free(copy); // FREES MEMORY

  return EXIT_SUCCESS;
}

/* EXPLICACION

 Inicialmente el ejercicio comienza asi.

 char *string_clone(const char *str, size_t length) {
   char clon[MAX_LENGTH]; // Es una variable local que vive en el stack
   char *output = clon;   // Apunta a una variable del stack
  for (size_t i = 0; i < length; i++) {
    output[i] = str[i];
  }
  output[length] = '\0';
  return output; // Output points to an address in the heap
}

El problema aqui es que clon[MAX_LENGTH] termina siendo un string local a la
funcion, es decir vive y muere en el stack.

Ademas, char *output seria un puntero a ese string, una vez la funcion muere, el
string del stack no existe mas entonces el puntero estaria apuntando a memoria
que ya no almacena el string que yo queria devolver.

Para solucionarlo hago que el output de la funcion sea un puntero a memoria
dinamica en el heap, cosa que al final de la funcion ese resultado que calcule
persista y no muera al retornar la funcion.

Inicialmente podria intentar hacer esto

 char *string_clone(const char *str, size_t length) {
   char *output = malloc(sizeof(*output) * length)
  for (size_t i = 0; i < length; i++) {
    output[i] = str[i];
  }
  output[length] = '\0';
  return output;
}

Aqui reserve length bytes es decir voy desde output[0] hasta output[length-1].
Como todo string debe terminar con el caracter nulo, al hacer output[length]
Valgrind me diria `invalid write of size 1` porque efectivamente estaria
solamente escribiendo 1 byte en memoria que no me pertenece.

Como yo quiero hacer un string valido que termine con el caracter nulo '\0'
entonces me gustaria poder escribir sobre la posicion output[length] que es el
byte length+1 si comienzo a contar desde el 0.

Para ello hago

  char *string_clone(const char *str, size_t length) {
    char *output = malloc(sizeof(*output) * length + 1) for (size_t i = 0;
                                                             i < length; i++) {
      output[i] = str[i];
    }
    output[length] = '\0';
    return output;
  }

Notar que ahora cada vez que yo llamo a string_clone() estare reservando memoria
en el heap que luego sera responsabilidad mia desalocar, es por eso que al final
del programa hago

  char *copy = NULL;
  copy = string_clone(original,
                      sizeof(original) / sizeof(*original)); // ALLOCATES MEMORY
  // ...
  free(copy); // FREES MEMORY

*/
