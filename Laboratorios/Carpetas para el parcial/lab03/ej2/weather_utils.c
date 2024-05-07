#include "weather_utils.h"
#include "array_helpers.h"
#include "limits.h"

int lowest_temp_ever(WeatherTable a) {
  int all_time_lowest_temp = INT_MAX;

  for (unsigned int year = 0u; year < YEARS; ++year) {
    for (month_t month = january; month <= december; ++month) {
      for (unsigned int day = 0u; day < DAYS; ++day) {
        if (a[year][month][day]._min_temp < all_time_lowest_temp) {
          all_time_lowest_temp = a[year][month][day]._min_temp;
        }
      }
    }
  };
  return all_time_lowest_temp;
}

void build_array_max_temperature(WeatherTable a, int output[YEARS]) {
  for (unsigned int year = 0u; year < YEARS; ++year) {
    int yearly_highest_temp = INT_MIN;
    // yearly_highest_temp = a[year][0][0]._max_temp;
    for (month_t month = january; month <= december; ++month) {
      for (unsigned int day = 0u; day < DAYS; ++day) {
        if (a[year][month][day]._max_temp > yearly_highest_temp) {
          yearly_highest_temp = a[year][month][day]._max_temp;
        };
      }
    }
    output[year] = yearly_highest_temp;
  }
}

void build_array_max_rainfall_months(WeatherTable a, int output[YEARS]) {
  // int *output

  for (unsigned int year = 0u; year < YEARS; ++year) {
    month_t month_with_the_highest_rainfall_acum = january;
    unsigned int highest_rainfall_acum_in_a_month_so_far = 0u;

    for (month_t month = january; month <= december; ++month) {
      unsigned int sum_rainfall = 0u;

      for (unsigned int day = 0u; day < DAYS; ++day) {
        sum_rainfall = sum_rainfall + a[year][month][day]._rainfall;
      }

      if (sum_rainfall >= highest_rainfall_acum_in_a_month_so_far) {
        highest_rainfall_acum_in_a_month_so_far = sum_rainfall;
        month_with_the_highest_rainfall_acum = month; // month_t
                                                      // january == 0
      }
    }
    output[year] = month_with_the_highest_rainfall_acum;
  }
}


