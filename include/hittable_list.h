#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include "common.h"
#include "hittable.h"
#include "sphere.h"
// struct hit_record_arr {
//   hit_record *array;
//   size_t used;
//   size_t size;
// } typedef hit_record_arr;
typedef struct sphere_arr {
  sphere *array;
  size_t used;
  size_t size;
} sphere_arr;
void init_sphere_arr(sphere_arr *h, size_t initial_size);
void insert_sphere_arr(sphere_arr *h, sphere element);
void free_sphere_arr(sphere_arr *h);
bool iter_spheres(sphere_arr *h, ray r, double tmin, double tmax,
                  hit_record *rec);
#endif
