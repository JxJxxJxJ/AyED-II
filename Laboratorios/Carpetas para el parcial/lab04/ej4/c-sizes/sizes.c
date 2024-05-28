#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void print_data(data_t d) {
  printf("NOMBRE: %s\n"
         "EDAD  : %d años\n"
         "ALTURA: %d cm\n\n",
         d.name, d.age, d.height);
}

void print_data_piola(data_t *d) {
  printf("NOMBRE: %s,\n    Direccion: %p\n    Tamaño: %lu\n"
         "EDAD  : %u años\n    Direccion: %p\n    Tamaño: %lu\n"
         "ALTURA: %u cm\n    Direccion: %p\n    Tamaño: %lu\n",
         d->name, (void *)&d->name, sizeof(d->name),        //
         d->age, (void *)&d->age, sizeof(d->age),           //
         d->height, (void *)&d->height, sizeof(d->height)); //
  //
  printf("Suma de los tamaños de NOMBRE, EDAD, ALTURA: %lu\n"
         "Tamaño total de la estructura: %lu \n\n",
         sizeof(d->name) + sizeof(d->age) + sizeof(d->height), sizeof(*d));
}

int main(void) {

  data_t messi = {"Leo Messi", 36, 169};
  print_data(messi);

  data_t *d = &messi;
  print_data_piola(d);

  return EXIT_SUCCESS;
}
