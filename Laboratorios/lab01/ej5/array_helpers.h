// I want to include array_helpers.h ONLY ONCE, to avoid redefinition problems
#ifndef ARRAY_HELPERS_H // If ARRAY_HELPERS_H was not defined, it means the file
                        // `array_helpers.h` was not previously included.
#define ARRAY_HELPERS_H // Then define ARRAY_HELPERS_H to avoid future
                        // inclusions problems, and go on with whatever
                        // array_helper.h does

#include "mybool.h" // This time with my own boolean library

unsigned int array_from_file(int array[], unsigned int max_size,
                             const char *filepath);
// Input: Array. Array Length. File with two lines where.
//    Line 1: unsigned int N.
//    Line 2: list of N integers.
// Output: The length of the array created.

// Description: Takes an array of length `max_size` and reads a file in
// `filepath`. It then populates the array with the elements specified in the
// file.

// Example:
// File1:
// 10
// 1 2 3 4 5 6 7 8 9 10
// array_from_file(array,N>=10,path/to/file/1) creates an
// array = [1,2,3,4,5,6,7,8,9,10] and outputs 10.

void array_dump(int a[], unsigned int length);
// Input: Array. Array Length.
// Output: Prints the array formatted in stdout.

// Description: Prints an array in a beautiful manner.

// Example:
// array[5] = {1,2,3,4,5}
// array_dump(array,5) outputs in stdout
// [1, 2, 3, 4, 5]

mybool array_is_sorted(int a[], unsigned int length);
// Input: Array. Array Length.
// Output: Returns if the array is sorted using a boolean value from stdbool.h.
// Also prints in stdout if the array is sorted or not.

// Example:
// array[5] = {1,2,3,4,5}
// array_is_sorted(array,5) returns true and prints in stdout
// "The array is sorted" <- (More or less lol)

#endif
