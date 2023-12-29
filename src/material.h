#ifndef MATERIAL_H
#define MATERIAL_H
#include "common.h"
enum Materials { LAMBERTIAN, METAL, DIELECTRIC };
typedef struct material {
  enum Materials material;
  vec3 albedo;
  double fuzz; // METAL
  double ir;   // DIELECTRIC
} material;
#endif // !MATERIAL_H
