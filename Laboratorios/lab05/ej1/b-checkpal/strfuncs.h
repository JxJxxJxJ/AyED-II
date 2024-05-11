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

bool string_is_symmetric(const char *str);
/*
    Returns whether the string is symmetric or not.
    Examples: 'aba', 'abba', 'abccba'.
*/
#endif
