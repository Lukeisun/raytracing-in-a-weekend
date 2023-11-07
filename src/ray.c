#include "../include/common.h"
vec3 at(ray r, double t) {
  vec3 scaled_vec = scalar_mult(r.direction, t);
  return add_vec(r.origin, scaled_vec);
}
