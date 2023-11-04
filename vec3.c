#include "vec3.h"
#include <math.h>
void print_vec(vec3 v) { printf("[%f, %f, %f]\n", v.x, v.y, v.z); }
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
vec3 mult_vec(vec3 v, vec3 o) {
  double x = v.x * o.x;
  double y = v.y * o.y;
  double z = v.z * o.z;
  return (vec3){x, y, z};
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
double length(vec3 v) { return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
