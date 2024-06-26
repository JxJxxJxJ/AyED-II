#include "dict.h"
#include "key_value.h"
#include "string.h"
#include <assert.h>
#include <stdlib.h>

struct _node_t {
  dict_t left;
  dict_t right;
  key_t key;
  value_t value;
};

static bool invrep(dict_t dict) {
  bool b;

  if (dict_is_empty(dict)) {
    b = true;
  } else {
    b = (dict_is_empty(dict->left) ||
         (key_less(dict->left->key, dict->key) && invrep(dict->left))) &&
        (dict_is_empty(dict->right) ||
         (key_less(dict->key, dict->right->key) && invrep(dict->right)));
  }

  return b;
}

dict_t dict_empty(void) {
  dict_t dict = NULL;
  assert(invrep(dict) && dict_length(dict) == 0);
  return dict;
}

bool dict_is_empty(dict_t dict) { return dict == NULL; }

dict_t dict_add(dict_t dict, key_t word, value_t def) {
  assert(invrep(dict));
  if (dict_exists(dict, word)) {
    if (key_eq(dict->key, word)) {
      dict->value = def;
    } else {
      if (key_less(word, dict->key)) {
        dict->left = dict_add(dict->left, word, def);
      } else {
        dict->right = dict_add(dict->right, word, def);
      }
    }
  } else {
    if (dict_is_empty(dict)) {
      dict = malloc(sizeof(*dict));
      dict->left = NULL;
      dict->right = NULL;
      dict->key = word;
      dict->value = def;
    } else {
      if (key_less(word, dict->key)) {
        dict->left = dict_add(dict->left, word, def);
      } else {
        dict->right = dict_add(dict->right, word, def);
      }
    }
  }

  assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
  return dict;
}

value_t dict_search(dict_t dict, key_t word) {
  assert(invrep(dict));
  key_t def = NULL;

  if (dict_exists(dict, word)) {
    if (key_eq(dict->key, word)) {
      def = dict->value;
    } else {
      if (key_less(word, dict->key)) {
        def = dict_search(dict->left, word);
      } else {
        def = dict_search(dict->right, word);
      }
    }
  }

  assert(invrep(dict) && ((def != NULL) == dict_exists(dict, word)));
  return def;
}

bool dict_exists(dict_t dict, key_t word) {
  assert(invrep(dict));

  bool exist = false;

  if (!dict_is_empty(dict)) {
    if (key_eq(dict->key, word)) {
      exist = true;
    } else {
      if (key_less(word, dict->key)) {
        exist = dict_exists(dict->left, word);
      } else {
        exist = dict_exists(dict->right, word);
      }
    }
  }

  assert(invrep(dict));
  return exist;
}

unsigned int dict_length(dict_t dict) {
  assert(invrep(dict));
  unsigned int length = 0u;
  if (!dict_is_empty(dict)) {
    length = 1 + dict_length(dict->right) + dict_length(dict->left);
  }
  return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
  assert(invrep(dict));
  if (dict_exists(dict, word)) {
    if (key_less(word, dict->key)) {
      dict->left = dict_remove(dict->left, word);
    }

    else if (key_less(dict->key, word)) {
      dict->right = dict_remove(dict->right, word);
    }

    else {
      if (dict_is_empty(dict->right) && dict_is_empty(dict->left)) {
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = NULL;
      }

      else if (dict_is_empty(dict->right)) {
        dict_t temp = dict;
        dict = dict->left;
        temp->key = key_destroy(temp->key);
        temp->value = value_destroy(temp->value);
        free(temp);
        temp = NULL;
      }

      else if (dict_is_empty(dict->left)) {
        dict_t temp = dict;
        dict = dict->right;
        temp->key = key_destroy(temp->key);
        temp->value = value_destroy(temp->value);
        free(temp);
        temp = NULL;
      }

      else {
        key_t min_key = dict_min(dict->right);
        value_t min_key_def = dict_search(dict, min_key);

        dict->key = min_key;
        dict->value = min_key_def;

        dict->right = dict_remove(dict->right, min_key);
      }
    }
  }

  assert(invrep(dict) && !dict_exists(dict, word));
  return dict;
}

key_t dict_min(dict_t dict) {
  assert(invrep(dict) && !dict_is_empty(dict));
  key_t min_key;

  if (!dict_is_empty(dict->left)) {
    min_key = dict_min(dict->left);
  } else {
    min_key = dict->key;
  }
  assert(invrep(dict) && dict_exists(dict, min_key));
  return min_key;
}

dict_t dict_remove_all(dict_t dict) {
  assert(invrep(dict));

  if (!dict_is_empty(dict)) {
    dict->left = dict_remove_all(dict->left);
    dict->right = dict_remove_all(dict->right);
    dict = dict_remove(dict, dict->key);
  }

  assert(invrep(dict) && dict_length(dict) == 0);
  return dict;
}

void dict_dump(dict_t dict, FILE *file) {
  if (!dict_is_empty(dict)) {

    key_dump(dict->key, file);
    printf(": ");
    value_dump(dict->value, file);
    printf("\n");

    dict_dump(dict->left, file);

    dict_dump(dict->right, file);
  }
}

dict_t dict_destroy(dict_t dict) {
  assert(invrep(dict));

  dict = dict_remove_all(dict);

  assert(dict == NULL);
  return dict;
}
