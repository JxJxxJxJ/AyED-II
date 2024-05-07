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

// Description: Prints an array in a beautiful manner.

// Example:
// array[5] = {1,2,3,4,5}
// array_dump(array,5) outputs in stdout
// [1, 2, 3, 4, 5]
