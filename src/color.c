#include "../include/color.h"
#include "../include/common.h"
void linear_to_gamma(vec3 *linear_vec) {
  linear_vec->x = sqrt(linear_vec->x);
  linear_vec->y = sqrt(linear_vec->y);
  linear_vec->z = sqrt(linear_vec->z);
}
void write_color(vec3 color, int samples_per_pixel) {
  interval intensity = {0, 0.999};
  double scale = 1.0 / samples_per_pixel;
  color = scalar_mult(color, scale);
  linear_to_gamma(&color);
  int iR = (int)(256 * clamp(intensity, color.x));
  int iG = (int)(256 * clamp(intensity, color.y));
  int iB = (int)(256 * clamp(intensity, color.z));
  printf("%d %d %d\n", iR, iG, iB);
}
