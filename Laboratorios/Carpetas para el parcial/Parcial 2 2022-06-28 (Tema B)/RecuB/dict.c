#include "dict.h"
#include "string.h"
#include <assert.h>
#include <stdlib.h>

struct _dict_t {
  node_t words;
  node_t defs;
  unsigned int length;
};

struct _node_t {
  string str;
  node_t next;
};

static bool invrep(dict_t d) {
  bool b = true;
  if (d == NULL) {
    b = false;
  } else if (dict_is_empty(d)) {
    b = d->length == 0;
  } else {
    node_t p = d->words;
    node_t q = d->defs;

    while (p->next != NULL) {

      if (!string_less(p->str, p->next->str)) {
        return false; // devuelvo false si no esta ordenado segun string_less
      }
      p = p->next;
      q = q->next;

      if ((p == NULL && q != NULL) || (q == NULL && p != NULL)) {
        return false; // devuelvo false si no tengo misma cantidad de defs que
                      // words
      }
    }
  }
  return b;
}

// returns the amount of nodes to skip when adding a new word
static int nodes_to_skip(dict_t dict, string word) {
  assert(invrep(dict));
  unsigned int numberToSkip = 0;

  node_t node = dict->words;
  while (node != NULL && string_less(node->str, word)) {
    numberToSkip++;
    node = node->next;
  }
  return numberToSkip;
}

// returns the position of the word on the list of nodes (0 being the first
// node) returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
  int index = 0;

  node_t nodo = dict->words;

  while (nodo != NULL) {
    if (string_eq(word, nodo->str)) {
      // si encuentro la palabra en el dict, devuelvo el index actual
      return index;
    }
    index++;
    nodo = nodo->next;
  }

  // a este return solamente llego si no encontre la palabra en el dict
  return -1;
}

dict_t dict_empty(void) {
  dict_t dict = NULL;
  dict = malloc(sizeof(*dict));
  assert(dict != NULL);
  dict->length = 0u;
  dict->words = NULL;
  dict->defs = NULL;
  assert(invrep(dict));
  return dict;
}

static node_t create_node(string elem) {
  node_t new_node = NULL;
  new_node = malloc(sizeof(*new_node));
  assert(new_node != NULL);
  new_node->str = elem;
  new_node->next = NULL;
  return new_node;
}

static node_t destroy_node(node_t node) {
  assert(node != NULL);
  node->str = string_destroy(node->str);
  free(node);
  return NULL;
}

bool dict_is_empty(dict_t dict) {
  return dict->words == NULL && dict->defs == NULL;
}

dict_t dict_add(dict_t dict, string word, string def) {
  assert(invrep(dict));
  if (dict_is_empty(dict)) { // Si esta vacio lo agrego de una
    dict->words = create_node(word);
    dict->defs = create_node(def);
    dict->length++;
  }

  else { // Si no esta vacio tengo que ver donde agregarlo
    int index = find_index_of_key(
        dict, word); // Esto calculaba el indice de una palabra ya en el
                     // diccionario, si la palabra no existe devuelve -1

    if (index == -1) { // Si la palabra no existe, busco donde ponerla y lo hago
      int skips = nodes_to_skip(dict, word); // Calculo donde ponerlo

      node_t word_to_add = create_node(word);
      node_t def_to_add = create_node(def);

      if (skips == 0) { // No existe y debo ponerlo al principio
        word_to_add->next = dict->words;
        def_to_add->next = dict->defs;

        dict->words = word_to_add;
        dict->defs = def_to_add;
      }

      else { // skips != 0 // No existe y debo ponerlo en algun otro lugar mas
             // adelante
        node_t p = dict->words;
        node_t q = dict->defs;

        for (int i = 0; i < skips - 1; i++) { // Me paro hasta uno antes
          p = p->next;
          q = q->next;
        } // p apunta al elemento skips - 1 en words
          // q apunta al elemento skips - 1 en defs

        // Y lo agrego, la palabra nueva apunta a lo que esta adelante
        word_to_add->next = p->next;
        def_to_add->next = q->next;

        // Lo que esta atras apunta a la palabra nueva
        p->next = word_to_add;
        q->next = def_to_add;
      }
      dict->length++;
    }

    else { // if index != 1 La palabra ya existe y solo debo reemplazar la
           // definicion
      node_t q = dict->defs;
      for (int i = 0; i < index; i++) {
        q = q->next;
      }
      // q apunta al elemento i de defs
      q->str = string_destroy(q->str); // Borro lo que habia antes
      q->str = string_clone(def);      // Meto lo que tenia en el string def
    }
  }

  assert(invrep(dict));
  assert(string_eq(def, dict_search(dict, word)));
  return dict;
}

string dict_search(dict_t dict, string word) {
  assert(invrep(dict));

  if (dict_exists(dict, word)) {               // Si existe
    int index = find_index_of_key(dict, word); // calculo el indice
    node_t p = dict->defs;                     // comenzando desde el inicio
    for (int i = 0; i < index; i++) {          // voy hasta alli
      p = p->next;
    }

    return p->str; // y leo lo que habia
  }

  else {
    return NULL;
  }
}

bool dict_exists(dict_t dict, string word) {
  assert(invrep(dict));

  bool exist = false;
  if (!dict_is_empty(dict)) {
    node_t palabra;
    palabra = dict->words;
    while (palabra != NULL && !exist) {
      if (string_eq(palabra->str, word)) {
        exist = true;
      }
      palabra = palabra->next;
    }
  }

  assert(invrep(dict));
  return exist;
}

unsigned int dict_length(dict_t dict) {
  assert(invrep(dict));
  return dict->length;
}

// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, int index) {
  assert(list != NULL);
  if (index != 0) {
    node_t p = list;
    node_t q;
    for (int i = 0; i < index; i++) {
      q = p;
      p = p->next;
    } // p -> elem esta en la posicion index
      // q esta en la anterior
      // q -> p -> elem_index
    q->next = p->next;
    p = destroy_node(p);
  }

  else { // index == 0, creo que tiene bug? anda pero no se
    node_t p = list;
    node_t q = p->next;
    p = destroy_node(p);
    return q;
  }
  return list;
}

dict_t dict_remove(dict_t dict, string word) {
  assert(invrep(dict));

  int index = find_index_of_key(dict, word);
  if (index != -1) {
    dict->words = remove_on_index(dict->words, index);
    dict->defs = remove_on_index(dict->defs, index);
    dict->length--;
  }

  assert(invrep(dict));
  return dict;
}

dict_t dict_remove_all(dict_t dict) {
  assert(invrep(dict));

  while (!dict_is_empty(dict)) {
    dict = dict_remove(dict, dict->words->str);
  }

  assert(invrep(dict));
  return dict;
}

void dict_dump(dict_t dict, FILE *file) {
  assert(invrep(dict));
  node_t p = dict->words;
  node_t q = dict->defs;

  for (unsigned int i = 0; i < dict->length; i++) {
    fprintf(file, "%s : %s\n", string_ref(p->str), string_ref(q->str));
    p = p->next;
    q = q->next;
  }
}

dict_t dict_destroy(dict_t dict) {
  assert(invrep(dict));

  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;

  return dict;
}