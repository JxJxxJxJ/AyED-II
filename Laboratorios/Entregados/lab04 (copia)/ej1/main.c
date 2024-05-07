/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
  int age;
  char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

  int x = 1;
  person_t m = {90, 'M'};
  int a[] = {0, 1, 2, 3};

  // declare p and use it to modify everything
  int *p;

  // modify x
  p = &x;
  *p = 9;
  printf("x = %d\n", x);

  // modify m.age
  p = &m.age;
  *p = 100;

  char *q;
  q = &m.name_initial;
  *q = 'F';
  printf("m = (%d, %c)\n", m.age, m.name_initial);

  // modify a[1]
  p = &a[1];
  *p = 42;

  printf("a[1] = %d\n", a[1]);

  return EXIT_SUCCESS;
}
