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
  const double R = cos(PI / 4);
  material m_left = {.material = LAMBERTIAN, .albedo = {0, 0, 1}};
  material m_right = {.material = LAMBERTIAN, .albedo = {1, 0, 0}};

  // material material_ground = {.material = LAMBERTIAN,
  //                             .albedo = (vec3){0.8, 0.8, 0.0}};
  // material material_center = {.material = LAMBERTIAN,
  //                             .albedo = (vec3){0.1, 0.2, 0.5}};
  // material material_left = {.material = DIELECTRIC, .ir = 1.5};
  // material material_right = {
  //     .material = METAL, .albedo = (vec3){0.8, 0.6, 0.2}, .fuzz = 0.0};
  // // material material_center = {.material = DIELECTRIC, .ir = 1.5};
  // // material material_left = {
  // //     .material = METAL, .albedo = (vec3){0.8, 0.8, 0.8}, .fuzz = 0.3};
  init_sphere_arr(&spheres, 10);
  insert_sphere_arr(&spheres, (sphere){{-R, 0, -1}, R, &m_left});
  insert_sphere_arr(&spheres, (sphere){{R, 0, -1}, R, &m_right});
  // insert_sphere_arr(&spheres,
  //                   (sphere){(vec3){0, 0, -1}, 0.5, &material_center});
  // insert_sphere_arr(&spheres,
  //                   (sphere){(vec3){0, -100.5, -1}, 100, &material_ground});
  // insert_sphere_arr(&spheres, (sphere){(vec3){-1, 0, -1}, 0.5,
  // &material_left}); insert_sphere_arr(&spheres,
  //                   (sphere){(vec3){-1, 0, -1}, -0.4, &material_left});
  // insert_sphere_arr(&spheres, (sphere){(vec3){1, 0, -1}, 0.5,
  // &material_right});
  vec3 look_from = {0, 0, -1};
  vec3 look_at = {0, 0, 0};
  camera cam = init_camera(400, look_from, look_at);
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;
  clock_t begin = clock();
  render(&cam, &spheres);
  clock_t end = clock();
  fprintf(stderr, "Time to render: %f seconds\n",
          (double)(end - begin) / CLOCKS_PER_SEC);
  free_sphere_arr(&spheres);
}
