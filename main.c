#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>
vec3 ray_color(ray r);
vec3 ray_color(ray r) {
  vec3 unit_dir = unit_vector(r.direction);
  double a = 0.5 * (unit_dir.y + 1.0);
  // printf("%f\n", a);
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
  vec3 upper_left =
      sub_vec(sub_vec(sub_vec(camera_center, focal_vec), half_Vu), half_Vv);
  // sub_vec(camera_center, sub_vec(focal_vec, sub_vec(half_Vu, half_Vv)));
  // printf("Upper Left\n");
  // print_vec(upper_left);
  vec3 pixel00 = add_vec(upper_left, scalar_mult(add_vec(deltaU, deltaV), .5));
  // print_vec(pixel00);
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int i = 0; i < image_height; i++) {
    fprintf(stderr, "\rScanlines Remainig: %d\n", (image_height - i));
    for (int j = 0; j < image_width; j++) {
      vec3 pixel_center = add_vec(
          pixel00, add_vec(scalar_mult(deltaU, j), scalar_mult(deltaV, i)));
      vec3 ray_dir = sub_vec(pixel_center, camera_center);
      ray r = {camera_center, ray_dir};
      vec3 pixel_color = ray_color(r);
      write_color(pixel_color);
    }
  }
}
