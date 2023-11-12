#ifndef VEC3_H
#define VEC3_H
#include <stdio.h>
typedef struct vec3 {
  double x;
  double y;
  double z;
} vec3;
bool eq_vec(vec3 v, vec3 o);
void print_vec(vec3 v);
vec3 add_vec(vec3 v, vec3 o);
vec3 sub_vec(vec3 v, vec3 o);
vec3 vsub_vec(int size, ...);
vec3 negate_vec(vec3 v);
vec3 mult_vec(vec3 v, vec3 o);
vec3 scalar_div(vec3 v, double scalar);
vec3 scalar_mult(vec3 v, double scalar);
vec3 scalar_add(vec3 v, double scalar);
vec3 unit_vector(vec3 v);
double dot(vec3 v, vec3 o);
double length(vec3 v);
vec3 random_vec();
vec3 random_vec_range(double min, double max);
vec3 random_vec_range(double min, double max);
vec3 random_in_unit_sphere();
vec3 random_unit_vector();
vec3 random_on_hemisphere(vec3 *norm);
#endif
