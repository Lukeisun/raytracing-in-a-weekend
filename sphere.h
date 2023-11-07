#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
#include "vec3.h"
#include <stdbool.h>
struct sphere {
  vec3 center;
  double radius;
} typedef sphere;
bool sphere_hit(sphere s, ray r, double tmin, double tmax, hit_record *rec);
#endif
