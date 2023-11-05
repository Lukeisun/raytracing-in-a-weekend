#ifndef VEC3_H
#define VEC3_H
#include <stdio.h>
struct vec3 {
  double x;
  double y;
  double z;
} typedef vec3;
void print_vec(vec3 v);
vec3 add_vec(vec3 v, vec3 o);
vec3 sub_vec(vec3 v, vec3 o);
vec3 vsub_vec(int size, ...);
vec3 mult_vec(vec3 v, vec3 o);
vec3 scalar_div(vec3 v, double scalar);
vec3 scalar_mult(vec3 v, double scalar);
vec3 scalar_add(vec3 v, double scalar);
vec3 unit_vector(vec3 v);
double length(vec3 v);
#endif
