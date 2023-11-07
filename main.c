#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

vec3 ray_color(ray r, sphere_arr *spheres) {
  hit_record *rec;
  if (iter_spheres(spheres, r, 0, INFINITY, rec)) {
    vec3 test = scalar_mult(add_vec(rec->normal, (vec3){1.0, 1.0, 1.0}), 0.5);
    return test;
  }
  vec3 unit_direction = unit_vector(r.direction);
  double a = 0.5 * (unit_direction.y + 1.0);
  return add_vec((scalar_mult((vec3){1.0, 1.0, 1.0}, 1.0 - a)),
                 scalar_mult((vec3){0.5, 0.7, 1.0}, a));
}
int main(void) {
  const double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = (int)(image_width / aspect_ratio);
  if (image_height < 1)
    image_height = 1;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)image_width / image_height);
  // distance from viewport to camera
  double focal_length = 1.0;
  vec3 camera_center = {0, 0, 0};
  vec3 viewport_u = {viewport_width, 0, 0};
  vec3 viewport_v = {0, -viewport_height, 0};
  // printf("ViewU\n");
  // print_vec(viewport_u);
  // printf("ViewV\n");
  // print_vec(viewport_v);
  vec3 deltaU = scalar_div(viewport_u, image_width);
  vec3 deltaV = scalar_div(viewport_v, image_height);
  vec3 half_Vu = scalar_div(viewport_u, 2.0);
  vec3 half_Vv = scalar_div(viewport_v, 2.0);
  vec3 half_sub = sub_vec(half_Vu, half_Vv);
  vec3 focal_vec = {0, 0, focal_length};
  // printf("Vv\n");
  // print_vec(half_Vv);
  // printf("Vu\n");
  // print_vec(half_Vu);
  // printf("focal - half\n");
  // print_vec(sub_vec(focal_vec, half_sub));
  vec3 upper_left = vsub_vec(4, camera_center, focal_vec, half_Vu, half_Vv);
  vec3 pixel00 = add_vec(upper_left, scalar_mult(add_vec(deltaU, deltaV), .5));
  // print_vec(pixel00);
  sphere_arr spheres;
  init_sphere_arr(&spheres, 10);
  insert_sphere_arr(&spheres, (sphere){(vec3){0, 0, -1}, 0.5});
  // insert_sphere_arr(&spheres, (sphere){(vec3){0, -100.5, -1}, 100});
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int i = 0; i < image_height; i++) {
    fprintf(stderr, "\rScanlines Remainig: %d\n", (image_height - i));
    for (int j = 0; j < image_width; j++) {
      vec3 pixel_center = add_vec(
          pixel00, add_vec(scalar_mult(deltaU, j), scalar_mult(deltaV, i)));
      vec3 ray_dir = sub_vec(pixel_center, camera_center);
      ray r = {camera_center, ray_dir};
      vec3 pixel_color = ray_color(r, &spheres);
      write_color(pixel_color);
    }
  }
}
