/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */

void print_help(char *program_name) {
  /* Print the usage help of this program. */
  printf("Usage: %s <input file path>\n\n", program_name);
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

abb abb_from_file(const char *filepath) {
  FILE *file = NULL;
  abb read_tree;

  read_tree = abb_empty();
  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }
  unsigned int i = 0u;
  unsigned int size = 0u;
  int res = 0;
  res = fscanf(file, " %u ", &size);
  if (res != 1) {
    fprintf(stderr, "Invalid format.\n");
    exit(EXIT_FAILURE);
  }
  while (i < size) {
    abb_elem elem;
    res = fscanf(file, " %d ", &(elem));
    if (res != 1) {
      fprintf(stderr, "Invalid array.\n");
      exit(EXIT_FAILURE);
    }
    read_tree = abb_add(read_tree, elem);

    ++i;
  }
  fclose(file);
  return read_tree;
}

void loop(abb tree) {
  tree = tree;

  bool stop = false;
  while (!stop) {
    printf( // Hecho por mi
        "  ╭─╮────────────────────────────────────────────────────╮\n"
        " ╭╯ ╰╮                                                   ╰╮\n"
        "╭╯   ╰╮    🌳  Mostrar árbol por pantalla               1 ╰╮\n"
        "│    ╭│                                                    ╰╮\n"
        "╰╮  ╭╯│    ➕  Agregar un elemento                      2   ╰╮\n"
        " ╰──╯ │                                                      │\n"
        "      │    ➖  Eliminar un elemento                     3    │\n"
        "      │                                                      │\n"
        "      │    ❓  Chequear existencia de elemento          4    │\n"
        "      │                                                      │\n"
        "      │    📏  Mostrar longitud del árbol               5    │\n"
        "      │                                                      │\n"
        "      │    🔎  Mostrar raiz, máximo y mínimo del árbol  6    │\n"
        "      ╰╮     ╭──╮──────────────────────────────────────────────────╮\n"
        "       ╰╮   ╭╯  ╰╮   🛑  Salir                               7     "
        "╰╮\n"
        "        ╰╮ ╭╯    "
        "╰──────────────────────────────────────────────────╯\n"
        "         ╰─╯─────────────────────────────────────────────────────╯\n");

    int option;

    scanf("%d", &option);

    switch (option) {
    case 1:
      abb_dump(tree, ABB_IN_ORDER);
      break;
    case 2: {
      abb_elem elem;
      printf("Ingrese el elemento a añadir:\n");
      scanf("%d", &elem);
      tree = abb_add(tree, elem);
      break;
    }
    case 3: {
      abb_elem elem;
      printf("Ingrese el elemento a eliminar:\n");
      scanf("%d", &elem);
      tree = abb_remove(tree, elem);
      break;
    }
    case 4: {
      abb_elem elem;
      printf("Ingrese el elemento a chequear:\n");
      scanf("%d", &elem);
      if (abb_exists(tree, elem)) {
        printf("El elemento %d existe en el árbol.\n", elem);
      } else {
        printf("El elemento %d no existe en el árbol.\n", elem);
      }
      break;
    }
    case 5:
      printf("La longitud del arbol es: %d\n", abb_length(tree));
      break;
    case 6:
      if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
               abb_min(tree), abb_max(tree));
      } else {
        printf("\nÁrbol vacío\n");
      }
      break;
    case 7:
      stop = true;
      break;
    default:
      printf("Opcion no valida\n");
      break;
    }
  }
}
/*
 * Modificar e implementar con un ciclo una interfaz que permita
 * al usuario realizar una de las siguientes operaciones en cada
 * iteración:
 *
 *
 *
 *    *    *    * 6 ........
 * 7 ........
 *
 * Se debe solicitar un número de entrada para realizar una de
 * las acciones.
 *
 * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que
 * ingrese el elemento a agregar, eliminar o chequear
 * respectivamente.
 *
 * Al salir debe liberarse toda la memoria utilizada.
 *
 */

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  /* parse the file to obtain an abb with the elements */
  abb tree = abb_from_file(filepath);

  loop(tree);

  tree = abb_destroy(tree);
  return (EXIT_SUCCESS);
}
