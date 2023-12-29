#ifndef RAY_H
#define RAY_H
#include "vec3.h"
typedef struct ray {
  vec3 origin; // in the book, vec3 is aliased as point3
  vec3 direction;
} ray;
vec3 at(ray r, double t);
#endif
