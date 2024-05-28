#include <stdbool.h>
#include <stdlib.h>

size_t string_length(const char *str) {
  size_t size = 0;
  for (unsigned i = 0; str[i] != '\0'; i++) {
    size++;
  }
  return size;
}

char *string_filter(const char *str, char c) {
  char *s_filtered = malloc(sizeof(char) * string_length(str) + 1);
  unsigned int i = 0;
  unsigned int j = 0;

  while (str[i] != '\0') {
    if (str[i] != c) {
      s_filtered[j] = str[i];
      j++;
      i++;
    } else if (str[i] == c) {
      i++;
    }
  }
  s_filtered[j] = '\0';
  return s_filtered;
}
/*
   Returns a new string with all chars different from c in the string pointed
   by str. Allocates memory.
*/

bool string_is_symmetric(const char *str) {
  bool b = true;
  if (*str == '\0') {
    b = true;
  } else if (*str != '\0') {
    unsigned int i = 0;
    unsigned int j = string_length(str) - 1;

    while (b && i < j) {
      if (str[i] == str[j]) {
        i++;
        j--;
      } else {
        b = false;
      }
    }
  }
  return b;
}
/*
    Returns whether the string is symmetric or not.
    Examples: 'aba', 'abba', 'abccba'.
*/
