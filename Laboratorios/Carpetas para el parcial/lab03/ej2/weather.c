/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include "weather.h"
#include <stdlib.h>

static const int AMOUNT_OF_WEATHER_VARS = 6;

Weather weather_from_file(FILE *file) {
  Weather weather;

  // ej de linea
  // 1980 1 1 10130 54 0 1980 1 2

  if (AMOUNT_OF_WEATHER_VARS !=
      fscanf(file, EXPECTED_WEATHER_FILE_FORMAT "\n", &weather._average_temp,
             &weather._max_temp, &weather._min_temp, &weather._pressure,
             &weather._moisture, &weather._rainfall)) {
    fprintf(stderr, "Error reading weather vars.\n");
    exit(EXIT_FAILURE);
  };

  return weather;
}

void weather_to_file(FILE *file, Weather weather) {
  fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, weather._average_temp,
          weather._max_temp, weather._min_temp, weather._pressure,
          weather._moisture, weather._rainfall);
}
