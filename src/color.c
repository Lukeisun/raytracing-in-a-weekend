#include "../include/color.h"
#include "../include/common.h"
void write_color(vec3 color) {
  int iR = (int)(255.99 * color.x);
  int iG = (int)(255.99 * color.y);
  int iB = (int)(255.99 * color.z);
  printf("%d %d %d\n", iR, iG, iB);
}
