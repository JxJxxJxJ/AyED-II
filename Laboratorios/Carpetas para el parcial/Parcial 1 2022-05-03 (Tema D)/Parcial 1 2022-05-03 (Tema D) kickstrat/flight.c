/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include "flight.h"
#include <stdlib.h>

static const int AMOUNT_OF_FLIGHT_VARS = 3;

Flight flight_from_file(FILE *file) {
  Flight flight;

  unsigned int hour;
  unsigned int delay;
  unsigned int passengers_amount;

  int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT " ", &hour, &delay,
                   &passengers_amount);

  if (res != AMOUNT_OF_FLIGHT_VARS) {
    fprintf(stderr, "Error reading the file. Check the file format.");
    exit(EXIT_FAILURE);
  }

  flight.hour = hour;
  flight.delay = delay;
  flight.passengers_amount = passengers_amount;

  return flight;
}
