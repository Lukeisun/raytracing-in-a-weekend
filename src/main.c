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
  init_sphere_arr(&spheres, 50);
  // BUBBLE
  // material material_ground = {.material = LAMBERTIAN,
  //                             .albedo = (vec3){0.8, 0.8, 0.0}};
  // material material_center = {.material = LAMBERTIAN,
  //                             .albedo = (vec3){0.1, 0.2, 0.5}};
  // material material_left = {.material = DIELECTRIC, .ir = 1.5};
  // material material_right = {
  //     .material = METAL, .albedo = (vec3){0.8, 0.6, 0.2}, .fuzz = 0.0};
  // init_sphere_arr(&spheres, 10);
  // insert_sphere_arr(&spheres,
  //                   (sphere){(vec3){0, 0, -1}, 0.5, &material_center});
  // insert_sphere_arr(&spheres,
  //                   (sphere){(vec3){0, -100.5, -1}, 100, &material_ground});
  // insert_sphere_arr(&spheres, (sphere){(vec3){-1, 0, -1}, 0.5,
  // &material_left}); insert_sphere_arr(&spheres,
  //                   (sphere){(vec3){-1, 0, -1}, -0.4, &material_left});
  // insert_sphere_arr(&spheres, (sphere){(vec3){1, 0, -1}, 0.5,
  // &material_right}); vec3 look_from = {-2, 2, 1}; vec3 look_at = {0, 0, -1};
  // BUBBLE END
  material ground = {.material = LAMBERTIAN, .albedo = {0.5, 0.5, 0.5}};
  insert_sphere_arr(&spheres, (sphere){(vec3){0, -1000, 0}, 1000, ground});
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      double choose_mat = random_double();
      vec3 center = {a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};
      if (length(sub_vec(center, (vec3){4, 0.2, 0})) > 0.9) {
        if (choose_mat < 0.8) {
          vec3 albedo = mult_vec(random_vec(), random_vec());
          material m = {.material = LAMBERTIAN, .albedo = albedo};
          insert_sphere_arr(&spheres, (sphere){center, 0.2, m});
        } else if (choose_mat < 0.95) {
          vec3 albedo = random_vec_range(0.5, 1);
          double fuzz = random_double_range(0, 0.5);
          material m = {.material = METAL, .albedo = albedo, .fuzz = fuzz};
          insert_sphere_arr(&spheres, (sphere){center, 0.2, m});
        } else {
          material m = {.material = DIELECTRIC, .ir = 1.5};
          insert_sphere_arr(&spheres, (sphere){center, 0.2, m});
        }
      }
    }
  }

  material mat1 = {.material = DIELECTRIC, .ir = 1.5};
  insert_sphere_arr(&spheres, (sphere){(vec3){0, 1, 0}, 1.0, mat1});
  material mat2 = {.material = LAMBERTIAN, .albedo = {0.4, 0.2, 0.1}};
  insert_sphere_arr(&spheres, (sphere){(vec3){-4, 1, 0}, 1.0, mat2});
  material mat3 = {.material = METAL, .albedo = {0.7, 0.6, 0.5}, .fuzz = 0};
  insert_sphere_arr(&spheres, (sphere){(vec3){4, 1, 0}, 1.0, mat3});
  vec3 look_from = {13, 2, 3};
  vec3 look_at = {0, 0, 0};
  camera cam = {.image_width = 1200,
                .look_at = look_at,
                .look_from = look_from,
                .samples_per_pixel = 500,
                .max_depth = 50,
                .vfov = 20,
                .defocus_angle = 0.6,
                .focus_dist = 10.0};
  init_camera(&cam);
  clock_t begin = clock();
  render(&cam, &spheres);
  clock_t end = clock();
  fprintf(stderr, "Time to render: %f seconds\n",
          (double)(end - begin) / CLOCKS_PER_SEC);
  free_sphere_arr(&spheres);
}
