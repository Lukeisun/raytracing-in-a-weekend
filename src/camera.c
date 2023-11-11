#include "../include/camera.h"
#include "../include/common.h"
#include <stdlib.h>
camera init_camera(int image_width, int samples_per_pixel) {
  camera cam = {.samples_per_pixel = samples_per_pixel};
  const double aspect_ratio = 16.0 / 9.0;
  cam.image_width = image_width;
  cam.image_height = (int)(cam.image_width / aspect_ratio);
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)cam.image_width / cam.image_height);
  // distance from viewport to camera
  double focal_length = 1.0;
  cam.center = (vec3){0, 0, 0};
  vec3 viewport_u = {viewport_width, 0, 0};
  vec3 viewport_v = {0, -viewport_height, 0};
  vec3 half_Vu = scalar_div(viewport_u, 2.0);
  vec3 half_Vv = scalar_div(viewport_v, 2.0);
  vec3 focal_vec = {0, 0, focal_length};
  vec3 upper_left = vsub_vec(4, cam.center, focal_vec, half_Vu, half_Vv);
  cam.pixel_delta_u = scalar_div(viewport_u, cam.image_width);
  cam.pixel_delta_v = scalar_div(viewport_v, cam.image_height);
  cam.pixel00 =
      add_vec(upper_left,
              scalar_mult(add_vec(cam.pixel_delta_u, cam.pixel_delta_v), .5));
  return cam;
}
void render(camera *cam, sphere_arr *spheres) {
  printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
  for (int i = 0; i < cam->image_height; i++) {
    fprintf(stderr, "\rScanlines Remainig: %d\n", (cam->image_height - i));
    for (int j = 0; j < cam->image_width; j++) {
      vec3 pixel_color = {0, 0, 0};
      for (int sample = 0; sample < cam->samples_per_pixel; sample++) {
        ray r = get_ray(cam, i, j);
        pixel_color = add_vec(pixel_color, ray_color(&r, spheres));
      }
      write_color(pixel_color, cam->samples_per_pixel);
    }
  }
}
vec3 ray_color(ray *r, sphere_arr *spheres) {
  hit_record *rec = malloc(sizeof(hit_record));
  interval initial_interval = {.min = 0, .max = INFINITY};
  if (iter_spheres(spheres, *r, initial_interval, rec)) {
    vec3 test = scalar_mult(add_vec(rec->normal, (vec3){1.0, 1.0, 1.0}), 0.5);
    return test;
  }
  vec3 unit_direction = unit_vector(r->direction);
  double a = 0.5 * (unit_direction.y + 1.0);
  return add_vec((scalar_mult((vec3){1.0, 1.0, 1.0}, 1.0 - a)),
                 scalar_mult((vec3){0.5, 0.7, 1.0}, a));
}
ray get_ray(camera *cam, int i, int j) {
  vec3 pixel_center =
      add_vec(cam->pixel00, add_vec(scalar_mult(cam->pixel_delta_u, j),
                                    scalar_mult(cam->pixel_delta_v, i)));
  vec3 pixel_sample = add_vec(pixel_center, pixel_sample_square(cam));
  vec3 ray_dir = sub_vec(pixel_sample, cam->center);
  return (ray){cam->center, ray_dir};
}
vec3 pixel_sample_square(camera *cam) {
  double px = -.5 + random_double();
  double py = -.5 + random_double();
  return add_vec(scalar_mult(cam->pixel_delta_u, px),
                 (scalar_mult(cam->pixel_delta_v, py)));
}
