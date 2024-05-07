// #include <assert.h>
#include "fixstring.h"
#include <stdbool.h>

unsigned int fstring_length(fixstring s) {
  unsigned int i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}

bool fstring_eq(fixstring s1, fixstring s2) {
  bool equal = true;
  unsigned int i = 0;

  while (equal && s1[i] != '\0' && s2[i] != '\0') { // if s1 & s2
    equal =
        s1[i] == s2[i]; // equal = equal && s1[i] == s2[i]; is redundant because
                        // equal is already true if it entered the while loop
    i++;
  }
  // if the loop exited then I have to check it was because of both of the
  // arrays and not only one
  if (fstring_length(s1) != fstring_length(s2)) {
    equal = false;
  }

  return equal;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
  bool less_eq = true;

  int pos_first_different = 0;
  while (s1[pos_first_different] == s2[pos_first_different] &&
         pos_first_different < FIXSTRING_MAX) {
    pos_first_different++;
  };

  // [pos_first_different] at the end of the loop
  // CASE 1: Same length
  // hola[\0]
  // hola[\0]
  //
  // CASE 2: Different length
  // hola[\0]
  // hola[s]as <-- comes later
  //
  // CASE 2: Different length
  // hola[s]as <-- comes later
  // hola[\0]

  // CASE 3: Difference in between
  // au[t]o
  // au[l]lido
  //
  // [c]asa
  // [b]arco

  // Then in all cases I have to compare
  // s1[pos_first_different] < s2[pos_first_different]

  if (s1[pos_first_different] <= s2[pos_first_different]) {
    less_eq = true;
  } else {
    less_eq = false;
  }

  // or just
  // less_eq = s1[pos_first_different] <= s2[pos_first_different];

  return less_eq;
}
