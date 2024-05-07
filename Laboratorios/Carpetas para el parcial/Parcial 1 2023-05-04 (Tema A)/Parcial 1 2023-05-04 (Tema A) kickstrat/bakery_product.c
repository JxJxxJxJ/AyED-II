/*
  @file bakery_product.c
  @brief Implements bakery product structure and methods
*/
#include "bakery_product.h"
#include <stdlib.h>

static const int AMOUNT_OF_PRODUCT_VARS = 7;

BakeryProduct bakery_product_from_file(FILE *file) {
  BakeryProduct product;
  // ejemplo
  // ##0??0 (200,10) (5,2) (30,15) 3720

  int res =
      fscanf(file, EXPECTED_PRODUCT_FILE_FORMAT, &product.flour_cant,
             &product.flour_price, &product.yeast_cant, &product.yeast_price,
             &product.butter_cant, &product.butter_price, &product.sale_value);

  if (res != AMOUNT_OF_PRODUCT_VARS) {
    fprintf(stderr, "Invalid product data.\n");
    exit(EXIT_FAILURE);
  }

  return product;
}
