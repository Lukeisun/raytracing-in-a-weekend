#ifndef INTERVAL_H
#define INTERVAL_H
#include <math.h>
typedef struct interval {
  double min;
  double max;
} interval;
bool contains(interval i, double x);
bool surrounds(interval i, double x);
double clamp(interval i, double x);
// shame, clangd alsdo doesnt like this
// if this becomes useful ill disable the warning
// constexpr interval empty = {0.07, INFINITY};
#endif
