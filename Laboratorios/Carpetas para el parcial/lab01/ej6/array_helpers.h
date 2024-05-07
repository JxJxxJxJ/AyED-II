// I want to include array_helpers.h ONLY ONCE, to avoid redefinition problems
#ifndef ARRAY_HELPERS_H // If ARRAY_HELPERS_H was not defined, it means the file
                        // `array_helpers.h` was not previously included.
#define ARRAY_HELPERS_H // Then define ARRAY_HELPERS_H to avoid future
                        // inclusions problems, and go on with whatever
                        // array_helper.h does

#include <stdbool.h>

unsigned int array_from_file(int array[], unsigned int max_size,
                             const char *filepath);
// Input: Array. Array Length. File with two lines where.
//    Line 1: unsigned int N.
//    Line 2: list of N integers.

// Description: Takes an array of length `max_size` and reads a file in
// `filepath`. It then populates the array with the elements specified in the
// file and returns the length of the array created.

// Example:
// File1:
// 10
// 1 2 3 4 5 6 7 8 9 10
// array_from_file(array,N>=10,path/to/file/1) creates an
// array = [1,2,3,4,5,6,7,8,9,10] and outputs 10.

void array_dump(int a[], unsigned int length);
// Input: Array. Array Length.

// Description: Prints an array in a beautiful manner.

// Example:
// array[5] = {1,2,3,4,5}
// array_dump(array,5) outputs in stdout
// [1, 2, 3, 4, 5]

bool array_is_sorted(int a[], unsigned int length);
// Input: Array. Array Length.

// Description: Returns if the array is sorted using a boolean value from
// stdbool.h. Also prints in stdout if the array is sorted or not.

// Example:
// array[5] = {1,2,3,4,5}
// array_is_sorted(array,5) returns true and prints in stdout
// "The array is sorted" <- (More or less lol)

void array_swap(int a[], unsigned int i, unsigned int j);
// Input: Array. Index i. Index j.

// Description:
// Takes an array an swap two elements, the ones on the position `i` and `j`.
// It does not check whether the indexes are valid indexes or not. They could be
// bigger than the array length...
//
// Example:
// array = {1,2,3}
// array_swap(array, 1, 2)
// now the array is [1,3,2].

void array_reverse(int a[], unsigned int length);
// Input: Array. Array Length.
//
// Description:
// Reverses all elements of an array.
//
// Example:
// array = {5,0,2,1,-5,2}
// array_reverse(array,5)
// now the array is [2,-5,1,2,0,5]
#endif
