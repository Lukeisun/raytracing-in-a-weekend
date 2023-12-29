#ifndef COMMON_H
#define COMMON_H
#include "interval.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdlib.h>
double random_double();
double random_double_range(double min, double max);
// have to supress unknown_typename as constexpr
// isnt supported in clangd yet
constexpr double PI = {3.1415926535897932385};
#endif
