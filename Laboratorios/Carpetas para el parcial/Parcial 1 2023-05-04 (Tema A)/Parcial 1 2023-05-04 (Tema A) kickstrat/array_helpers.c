/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include "array_helpers.h"
#include "bakery_product.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const int EXPECTED_DIM_VALUE = 2;

static const char *CITY_NAMES[CITIES] = {"Cordoba", "Rosario", "Posadas",
                                         "Tilcara", "Bariloche"};
static const char *SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a) {
  for (unsigned int city = 0u; city < CITIES; ++city) {
    for (unsigned int season = 0u; season < SEASONS; ++season) {
      fprintf(stdout,
              "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) "
              "Sales value %u",
              CITY_NAMES[city], SEASON_NAMES[season],
              a[city][season].flour_cant, a[city][season].flour_price,
              a[city][season].yeast_cant, a[city][season].yeast_price,
              a[city][season].butter_cant, a[city][season].butter_price,
              a[city][season].sale_value);
      fprintf(stdout, "\n");
    }
  }
}

unsigned int best_profit(BakeryProductTable a) {
  unsigned int max_profit = 0u;

  // find best bakery/season profit
  for (city_t city = Cordoba; city < CITIES; city++) {
    for (season_t season = low; season < SEASONS; season++) {
      unsigned int cost = 0;
      unsigned int sale_value = 0;
      unsigned int profit = 0;

      cost = (a[city][season].flour_cant * a[city][season].flour_price) +
             (a[city][season].yeast_cant * a[city][season].yeast_price) +
             (a[city][season].butter_cant * a[city][season].butter_price);

      sale_value = a[city][season].sale_value;

      profit = sale_value - cost;

      if (profit > max_profit) {
        max_profit = profit;
      }
    }
  }

  return max_profit;
}

void array_from_file(BakeryProductTable a, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int scanned_city;
  unsigned int scanned_season;
  BakeryProduct product;

  while (!feof(file)) {
    // for (city_t city = Cordoba; city < CITIES; city++) {
    // for (season_t season = low; season < SEASONS; season++) {

    int dim_value = fscanf(file, "##%u??%u ", &scanned_city, &scanned_season);

    if (dim_value != EXPECTED_DIM_VALUE) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    product = bakery_product_from_file(file);
    a[scanned_city][scanned_season] = product;
    // }
    // }
  }

  fclose(file);
}
