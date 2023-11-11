#include "../include/color.h"
#include "../include/common.h"
void write_color(vec3 color, int samples_per_pixel) {
  interval intensity = {0, 0.999};
  double scale = 1.0 / samples_per_pixel;
  color = scalar_mult(color, scale);
  int iR = (int)(256 * clamp(intensity, color.x));
  int iG = (int)(256 * clamp(intensity, color.y));
  int iB = (int)(256 * clamp(intensity, color.z));
  printf("%d %d %d\n", iR, iG, iB);
}
