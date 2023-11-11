#ifndef SPHERE_H
#define SPHERE_H
#include "common.h"
#include "hittable.h"
typedef struct sphere {
  vec3 center;
  double radius;
} sphere;
bool sphere_hit(sphere s, ray r, interval ray_t, hit_record *rec);
#endif
