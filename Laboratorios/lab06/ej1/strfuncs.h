#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdbool.h>
#include <stdlib.h> // needed for size_t

size_t string_length(const char *str);
/*
    Calculates the length of the string pointed by str.
*/

char *string_filter(const char *str, char c);
/*
   Returns a new string with all chars different from c in the string pointed
   by str. Allocates memory.
*/

char *string_concat(const char *s1, const char *s2);
/*
   Returns a new string with the concatenation of s1 and s2 in concat, is null
   terminated. Allocates memory.
*/

char *string_copy(const char *str);
/*
   Returns a copy of str. Allocates memory.
*/

bool string_is_symmetric(const char *str);
/*
    Returns whether the string is symmetric or not.
    Examples: 'aba', 'abba', 'abccba'.
*/

#endif
