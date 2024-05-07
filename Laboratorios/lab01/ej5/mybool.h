// mybool.h is included in
// array_helpers.c
// array_helpers.h
// main.c
// If I want to check whether mybool.h was included or not and only do it once I
// have to do the following check

#ifndef MYBOOL_H // "If MYBOOL_H was not previously defined"
#define MYBOOL_H // Define it.
                 // Since all the content from the file is inside this IF
                 // clause, basically what this does is it ONLY defines the
                 // functions in `mybool.h` IF they were NOT previously defined,
                 // avoiding redefinitions.

#define true 1
#define false 0
typedef int mybool;

// stdbool also adds a check for being able to know if both true and false were
// defined (or in my case, redefined) properly, a "signal"
#define __bool_true_false_are_redefined 1

#endif
