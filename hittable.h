#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>
struct hit_record {
  vec3 p;
  vec3 normal;
  double t;
  bool front_face;
} typedef hit_record;
void set_face_normal(hit_record *hit, ray r, vec3 outward_normal);
#endif
