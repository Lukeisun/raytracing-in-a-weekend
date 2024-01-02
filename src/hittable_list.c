#include "hittable_list.h"
#include "common.h"
#include "hittable.h"
#include "sphere.h"
#include <stdio.h>
#include <stdlib.h>

void init_sphere_arr(sphere_arr *h, size_t initial_size) {
  h->array = malloc(initial_size * sizeof(sphere));
  h->used = 0;
  h->size = initial_size;
}
void insert_sphere_arr(sphere_arr *h, sphere element) {
  if (h->used == h->size) {
    h->size *= 2;
    h->array = realloc(h->array, h->size * sizeof(sphere));
  }
  h->array[h->used++] = element;
}
void free_sphere_arr(sphere_arr *h) {
  free(h->array);
  h->array = NULL;
  h->size = h->used = 0;
}
bool iter_spheres(sphere_arr *h, ray r, interval ray_t, hit_record *rec) {
  bool hit_anything = false;
  double closest = ray_t.max;
  // maybe use _Generic if we add more shapes
  for (size_t i = 0; i < h->used; i++) {
    if (sphere_hit(h->array[i], r, (interval){.min = ray_t.min, .max = closest},
                   rec)) {
      hit_anything = true;
      closest = rec->t;
    }
  }
  return hit_anything;
}
