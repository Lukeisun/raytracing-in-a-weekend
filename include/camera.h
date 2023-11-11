#ifndef CAMERA_H
#define CAMERA_H
#include "color.h"
#include "common.h"
#include "hittable.h"
#include "hittable_list.h"
typedef struct camera {
  int image_width;
  int image_height;
  int samples_per_pixel;
  vec3 center;
  vec3 pixel00;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
} camera;

camera init_camera(int image_width, int samples_per_pixel);
void render(camera *cam, sphere_arr *spheres);
vec3 ray_color(ray *r, sphere_arr *spheres);
ray get_ray(camera *cam, int i, int j);
vec3 pixel_sample_square(camera *cam);
#endif