/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "flight.h"

/**
 * @brief returns true when reach last line in flight file
 * @return True when is the last line of the file, False otherwise
 */
static bool is_last_line(unsigned int hour, unsigned int type) {
  return hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DelayTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(
          stdout,
          "%c: %s flight with %u passengers arrived at %u:00, with %u delay",
          f.code, f.type == 0 ? "last_mile" : "layover", f.passengers_amount,
          f.hour - 1, f.delay);
      if (!is_last_line(hour, type)) {
        fprintf(stdout, "\n");
      }
    }
  }
}
// calculates how much to pay up to 6pm (18:00)
unsigned int compensation_cost(DelayTable a, unsigned int h) {
  unsigned int total_sum_to_pay = 0u;

  for (flight_t flight = last_mile; flight < TYPE; flight++) {
    for (unsigned int hour = 0u; hour < h; hour++)

      if (flight == last_mile && a[flight][hour].delay > MAX_LM_DELAY_ALLOWED) {
        unsigned int delay = a[flight][hour].delay;
        unsigned int passengers_amount = a[flight][hour].passengers_amount;

        total_sum_to_pay = total_sum_to_pay + (delay - MAX_LM_DELAY_ALLOWED) *
                                                  COMPENSATION_PER_MINUTE *
                                                  passengers_amount;
      }

      else if (flight == layover &&
               a[flight][hour].delay > MAX_LAYOVER_DELAY_ALLOWED) {
        unsigned int delay = a[flight][hour].delay;
        unsigned int passengers_amount = a[flight][hour].passengers_amount;

        total_sum_to_pay =
            total_sum_to_pay + (delay - MAX_LAYOVER_DELAY_ALLOWED) *
                                   COMPENSATION_PER_MINUTE * passengers_amount;
      };
  }

  return total_sum_to_pay;
}

void array_from_file(DelayTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  while (!feof(file)) {
    // -------------------------------------------
    // here I scan a line of file distinguishing between the fields properly
    Flight last_mile_info = flight_from_file(file);
    Flight layover_info = flight_from_file(file);
    last_mile_info.type = last_mile;
    layover_info.type = layover;

    int res = fscanf(file, EXPECTED_FLIGHT_CODE_FORMAT "\n", &code);

    if (res != 1) {
      fprintf(stderr, "Invalid file. (A flight code was not read properly.\n");
      exit(EXIT_FAILURE);
    }

    last_mile_info.code = code;
    layover_info.code = code;

    // -------------------------------------------

    // flight information about last_mile flights is on the first row,
    // flight information about layover   flights is on the second row,
    // each flight information cell is indexed depending its time of arrival

    array[last_mile][last_mile_info.hour - 1] = last_mile_info;
    array[layover][layover_info.hour - 1] = layover_info;
  }

  fclose(file);
}
