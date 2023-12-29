#include "common.h"
#include <math.h>
bool contains(interval i, double x) { return i.min <= x && x <= i.max; }
bool surrounds(interval i, double x) { return i.min < x && x < i.max; }
double clamp(interval i, double x) {
  if (x < i.min)
    return i.min;
  if (x > i.max)
    return i.max;
  return x;
}
