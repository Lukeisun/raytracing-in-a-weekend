#ifndef CAMERA_H
#define CAMERA_H
#include "hittable_list.h"
typedef struct camera {
  int image_width;
  int image_height;
  int samples_per_pixel;
  int max_depth;
  double vfov;
  double defocus_angle;
  double focus_dist;
  vec3 v_up;
  vec3 look_at;
  vec3 look_from;
  vec3 center;
  vec3 pixel00;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  vec3 defocus_disk_u;
  vec3 defocus_disk_v;
} camera;

void init_camera(camera *cam);
void render(camera *cam, sphere_arr *spheres);
vec3 ray_color(ray *r, int depth, sphere_arr *spheres);
ray get_ray(camera *cam, int i, int j);
vec3 pixel_sample_square(camera *cam);
#endif
