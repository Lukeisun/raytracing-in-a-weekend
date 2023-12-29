#include "common.h"
double random_double() { return rand() / (RAND_MAX + 1.0); }
double random_double_range(double min, double max) {
  return min + (max - min) * random_double();
}
