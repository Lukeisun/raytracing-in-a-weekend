#ifndef MATERIAL_H
#define MATERIAL_H
#include "common.h"
enum Materials { LAMBERTIAN, METAL };
typedef struct material {
  enum Materials material;
  vec3 albedo;
} material;
#endif // !MATERIAL_H
