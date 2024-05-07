#ifndef WEATHER_UTILS
#define WEATHER_UTILS

#include "array_helpers.h"

int lowest_temp_ever(WeatherTable a); // takes a weathertable and returns the
                                      // lowest temperature ever

void build_array_max_temperature(
    WeatherTable a,
    int output[YEARS]); // takes a weathertable and saves in output[years] the
                        // highest temperature recorded on that year

void build_array_max_rainfall_months(
    WeatherTable a,
    int output[YEARS]); // records the month of biggest ammount of rainfall
                        // on
// int &output[YEARS]); // records the month of biggest ammount of rainfall on
// each year and saves it in the output array

#endif
