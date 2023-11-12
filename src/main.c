#include "../include/camera.h"
#include "../include/color.h"
#include "../include/common.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  sphere_arr spheres;
  init_sphere_arr(&spheres, 10);
  insert_sphere_arr(&spheres, (sphere){(vec3){0, 0, -1}, 0.5});
  insert_sphere_arr(&spheres, (sphere){(vec3){0, -100.5, -1}, 100});
  camera cam = init_camera(400);
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;
  render(&cam, &spheres);
}
