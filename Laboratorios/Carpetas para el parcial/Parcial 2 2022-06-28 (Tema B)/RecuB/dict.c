#include "dict.h"
#include "string.h"
#include <assert.h>
#include <stdlib.h>

struct _dict_t {
  size_t size;
  node_t words;
  node_t definitions;
};

struct _node_t {
  string text;
  node_t next;
};

static bool invrep(dict_t d) {
  bool b = false;
  if (d != NULL) {
    b = true;
  };

  if (dict_length(d) == 0) {
    b = d->words == NULL && d->definitions == NULL;
  }

  return b;
}

// returns the amount of nodes to skip when adding a new word
static int nodes_to_skip(dict_t dict, string word) {
  unsigned int numberToSkip = 0;
  node_t p = dict->words;

  // bool b = false;

  if (dict_length(dict) == 0) {
    numberToSkip = 0;
  }

  else
    while (p != NULL) {
      if (string_less(p->text, word)) {
        numberToSkip++;
        p = p->next;
      }
    }

  return numberToSkip;
}

// returns the position of the word on the list of nodes (0 being the first
// node) returns -1 if the word is not on the dict
static int find_index_of_key(dict_t dict, string word) {
  int index = 0;
  bool found = false;

  node_t p = dict->words;

  size_t i = 0;
  while (!found && i < dict->size) {
    if (!string_eq(p->text, word)) {
      index++;
      p = p->next;
    } else if (string_eq(p->text, word)) {
      found = true;
    }
    i++;
  }
  return (found) ? index : -1;
}

dict_t dict_empty(void) {
  dict_t dict = malloc(sizeof(*dict));
  dict->definitions = NULL;
  dict->words = NULL;
  dict->size = 0u;
  return dict;
}

static node_t create_node(string elem) {
  node_t node = malloc(sizeof(*node));
  node->text = elem;
  node->next = NULL;
  return node;
}

static node_t destroy_node(node_t node) {
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

dict_t dict_add(dict_t dict, string word, string def) {

  node_t palabra = create_node(word);
  node_t definicion = create_node(def);

  int index = nodes_to_skip(dict, word);

  node_t p_words = dict->words;
  node_t p_defs = dict->definitions;

  int i = 0;
  while (i < index - 1) {
    p_words = p_words->next;
    p_defs = p_defs->next;
  } // i == index - 1

  palabra->next = p_words->next;
  p_words->next = palabra;

  definicion->next = p_defs->next;
  p_defs->next = definicion;
  // meto g, index 6, hasta que i = 5 (p_words -> f, p_defs -> fdef)
  // a    b    cde f    [ palabra ]    h    i    jk
  // adef bdef ... fdef [ definicion ] hdef idef ...
  dict->size++;
  return dict;
}

string dict_search(dict_t dict, string word) {

  node_t p = dict->words;
  node_t q = dict->definitions;

  while (p != NULL && !string_eq(p->text, word)) {
    p = p->next;
    q = q->next;
  }

  return (q != NULL) ? q->text : NULL;
}

bool dict_exists(dict_t dict, string word) {
  bool found = false;
  node_t p = dict->words;
  while (!found && p != NULL) {
    found = string_eq(p->text, word);
    p = p->next;
  }
  return found;
}

unsigned int dict_length(dict_t dict) { return dict->size; }

// removes the "index" element of the "list" list of nodes
static node_t remove_on_index(node_t list, int index) {
  node_t p = list;
  node_t killme = NULL;
  int i = 0u;
  while (i < index - 1) {
    p = p->next;
    i++;
  } // i == index - 1
  killme = p->next;
  p->next = p->next->next;
  destroy_node(killme);
  return list;
}

dict_t dict_remove(dict_t dict, string word) {
  assert(invrep(dict));
  int index = find_index_of_key(dict, word);
  if (index != -1) {
    dict->words = remove_on_index(dict->words, index);
    dict->definitions = remove_on_index(dict->definitions, index);
    dict->size--;
  }
  assert(invrep(dict));
  return dict;
}

dict_t dict_remove_all(dict_t dict) {
  node_t p = dict->words;
  node_t pkillme = NULL;
  node_t q = dict->definitions;
  node_t qkillme = NULL;

  for (unsigned int i = 0u; i < dict_length(dict); i++) {
    pkillme = p;
    qkillme = q;
    p = p->next;
    q = q->next;
    destroy_node(pkillme);
    destroy_node(qkillme);
  }

  dict->definitions = NULL;
  dict->words = NULL;
  return dict;
}

void dict_dump(dict_t dict, FILE *file) {

  /* COMPLETAR */
  /* tip: use fprintf(file, "%s : %s\n", string_ref(word), string_ref(def)); to
   * save to file  */
  node_t p = dict->words;
  node_t q = dict->definitions;

  for (unsigned int i = 0u; i < dict_length(dict); i++) {
    fprintf(file, "[W: %s | D: %s]", string_ref(p->text), string_ref(q->text));
    p = p->next;
    q = q->next;
  }
}

dict_t dict_destroy(dict_t dict) {
  dict = dict_remove_all(dict);
  free(dict);
  dict = NULL;
  return dict;
}
