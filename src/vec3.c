#include "common.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
void print_vec(vec3 v) { printf("[%f, %f, %f]\n", v.x, v.y, v.z); }
bool eq_vec(vec3 v, vec3 o) { return v.x == o.x && v.y == o.y && v.z == o.z; }
vec3 add_vec(vec3 v, vec3 o) {
  double x = v.x + o.x;
  double y = v.y + o.y;
  double z = v.z + o.z;
  return (vec3){x, y, z};
}
vec3 sub_vec(vec3 v, vec3 o) {
  double x = v.x - o.x;
  double y = v.y - o.y;
  double z = v.z - o.z;
  return (vec3){x, y, z};
}
vec3 vsub_vec(int size, ...) {
  va_list va;
  va_start(va, size);
  vec3 ret_vec = va_arg(va, vec3);
  for (int i = 1; i < size; i++) {
    vec3 curr = va_arg(va, vec3);
    ret_vec = sub_vec(ret_vec, curr);
  }
  va_end(va);
  return ret_vec;
}
vec3 mult_vec(vec3 v, vec3 o) {
  double x = v.x * o.x;
  double y = v.y * o.y;
  double z = v.z * o.z;
  return (vec3){x, y, z};
}
vec3 negate_vec(vec3 v) {
  v.x *= -1;
  v.y *= -1;
  v.z *= -1;
  return v;
}
vec3 scalar_mult(vec3 v, double scalar) {
  double x = v.x * scalar;
  double y = v.y * scalar;
  double z = v.z * scalar;
  return (vec3){x, y, z};
}
vec3 scalar_div(vec3 v, double scalar) {
  double x = v.x / scalar;
  double y = v.y / scalar;
  double z = v.z / scalar;
  return (vec3){x, y, z};
}
vec3 scalar_add(vec3 v, double scalar) {
  double x = v.x + scalar;
  double y = v.y + scalar;
  double z = v.z + scalar;
  return (vec3){x, y, z};
}
vec3 unit_vector(vec3 v) { return scalar_div(v, length(v)); }

double dot(vec3 v, vec3 o) { return (v.x * o.x) + (v.y * o.y) + (v.z * o.z); }
double length(vec3 v) { return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
vec3 random_vec() {
  return (vec3){random_double(), random_double(), random_double()};
}
vec3 random_vec_range(double min, double max) {
  return (vec3){random_double_range(min, max), random_double_range(min, max),
                random_double_range(min, max)};
}
vec3 random_in_unit_sphere() {
  while (true) {
    vec3 r = random_vec_range(-1, 1);
    if (dot(r, r) < 1)
      return r;
  }
}
vec3 random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

vec3 random_on_hemisphere(vec3 *norm) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, *norm) > 0.0)
    return on_unit_sphere;
  else
    return negate_vec(on_unit_sphere);
}
bool near_zero(vec3 *v) {
  double tolerance = 1e-8;
  return (fabs(v->x) < tolerance) && (fabs(v->y) < tolerance) &&
         (fabs(v->z) < tolerance);
}
vec3 reflect_vec(vec3 *v, vec3 *o) {
  vec3 reflected_vec = sub_vec(*v, scalar_mult(*o, 2 * dot(*v, *o)));
  return reflected_vec;
}
