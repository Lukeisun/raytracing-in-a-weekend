#include "camera.h"
#include "color.h"
#include "common.h"
#include "material.h"
#include <stdlib.h>
#include <string.h>
camera init_camera(int image_width) {
  camera cam = {0};
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
  // int size = (cam->image_width * cam->image_height + 1);
  // image_string should look like
  // [ colored █,colored █, ... colored █, \n, ...
  //   colored █,colored █, ... colored █, \n, \0]
  // is this UB?
  // not sure of a more concrete way to find this,
  // formatted string looks like
  // "\x1b[38;2;%d;%d;%dm█", r, g, b
  // \x1b is 1 byte, each %d could be 3 digits, and end string char is 1
  // █ is 4 bytes
  // where h = \x1b, E = \0, and %d = 100
  // "h[38;2;100;100;100m1234E" = 24
  // you can pretty much ignore all the image_string stuff.
  // I think at somepoint I will move printing to a terminal stuff
  // into another program as it doesnt really belong here.
  int max_size_of_pixel = 24;
  int max_size = cam->image_height * cam->image_width * max_size_of_pixel +
                 cam->image_height + 1;
  char *image_string = malloc(max_size);
  image_string[0] = '\0';
  for (int i = 0; i < cam->image_height; i++) {
    fprintf(stderr, "\rScanlines Remaining: %d\n", (cam->image_height - i));
    for (int j = 0; j < cam->image_width; j++) {
      vec3 pixel_color = {0, 0, 0};
      for (int sample = 0; sample < cam->samples_per_pixel; sample++) {
        ray r = get_ray(cam, i, j);
        pixel_color =
            add_vec(pixel_color, ray_color(&r, cam->max_depth, spheres));
      }
      write_color(pixel_color, cam->samples_per_pixel, &image_string);
    }
    // strncat(image_string, "\n", 2);
  }
  // fprintf(stderr, "%s", image_string);
  // printf("\x1b[0m");
  // free(image_string);
}
vec3 ray_color(ray *r, int depth, sphere_arr *spheres) {
  if (depth <= 0)
    return (vec3){0, 0, 0};
  hit_record *rec = malloc(sizeof(hit_record));
  interval initial_interval = {.min = 0.001, .max = INFINITY};
  if (iter_spheres(spheres, *r, initial_interval, rec)) {
    ray *scattered = malloc(sizeof(ray));
    vec3 *attenuation = malloc(sizeof(vec3));
    if (scatter(rec->mat, r, rec, attenuation, scattered)) {
      return mult_vec(*attenuation, ray_color(scattered, depth - 1, spheres));
    }
    return (vec3){0, 0, 0};
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
