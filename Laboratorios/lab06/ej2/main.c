#include "string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  string str1 = string_create("String 1");
  string str2 = string_create("String 2");
  string str3 = string_create("String 1");

  if (string_less(str1, str2)) {
    printf("\"%s\" es menor que \"%s\"\n", string_ref(str1), string_ref(str2));
  } else {
    printf("\"%s\" no es menor que \"%s\"\n", string_ref(str1),
           string_ref(str2));
  }

  if (string_eq(str1, str3)) {
    printf("\"%s\" es igual a \"%s\"\n", string_ref(str1), string_ref(str3));
  } else {
    printf("\"%s\" no es igual a \"%s\"\n", string_ref(str1), string_ref(str3));
  }

  string_destroy(str1);
  string_destroy(str2);
  string_destroy(str3);

  return (EXIT_SUCCESS);
}
