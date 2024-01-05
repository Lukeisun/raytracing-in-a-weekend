#include "camera.h"
#include "color.h"
#include "common.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  sphere_arr spheres;
  init_sphere_arr(&spheres, 10);
  material ground = {.material = LAMBERTIAN, .albedo = {0.5, 0.5, 0.5}};
  insert_sphere_arr(&spheres, (sphere){(vec3){0, -1000, 0}, 1000, &ground});
  material mat1 = {.material = DIELECTRIC, .ir = 1.5};
  insert_sphere_arr(&spheres, (sphere){(vec3){0, 1, 0}, 1.0, &mat1});
  material mat2 = {.material = LAMBERTIAN, .albedo = {0.4, 0.2, 0.1}};
  insert_sphere_arr(&spheres, (sphere){(vec3){-4, 1, 0}, 1.0, &mat2});
  material mat3 = {.material = METAL, .albedo = {0.7, 0.6, 0.5}, .fuzz = 0};
  insert_sphere_arr(&spheres, (sphere){(vec3){4, 1, 0}, 1.0, &mat3});
  vec3 look_from = {13, 2, 3};
  vec3 look_at = {0, 0, 0};
  camera cam = {.image_width = 1200,
                .look_at = look_at,
                .look_from = look_from,
                .samples_per_pixel = 500,
                .max_depth = 50,
                .vfov = 20,
                .defocus_angle = 0,
                .focus_dist = 10.0};
  init_camera(&cam);
  clock_t begin = clock();
  render(&cam, &spheres);
  clock_t end = clock();
  fprintf(stderr, "Time to render: %f seconds\n",
          (double)(end - begin) / CLOCKS_PER_SEC);
  free_sphere_arr(&spheres);
}
