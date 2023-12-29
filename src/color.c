#include "color.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
void linear_to_gamma(vec3 *linear_vec) {
  linear_vec->x = sqrt(linear_vec->x);
  linear_vec->y = sqrt(linear_vec->y);
  linear_vec->z = sqrt(linear_vec->z);
}
// Print color to term
char *pixel(int r, int g, int b) {
  // max 23 (just pirntf sizes)
  // x1b is one byte
  int needed_size = snprintf(NULL, 0, "\x1b[38;2;%d;%d;%dm█", r, g, b) + 1;
  char *ret = malloc(needed_size);
  if (ret == NULL) {
    exit(1);
  }
  snprintf(ret, needed_size, "\x1b[38;2;%d;%d;%dm█", r, g, b);
  return ret;
}
void write_color(vec3 color, int samples_per_pixel, char **image_string) {
  interval intensity = {0, 0.999};
  double scale = 1.0 / samples_per_pixel;
  color = scalar_mult(color, scale);
  linear_to_gamma(&color);
  int iR = (int)(256 * clamp(intensity, color.x));
  int iG = (int)(256 * clamp(intensity, color.y));
  int iB = (int)(256 * clamp(intensity, color.z));
  char *s = pixel(iR, iG, iB);
  strncat(*image_string, s, strlen(s));
  printf("%d %d %d\n", iR, iG, iB);
}
