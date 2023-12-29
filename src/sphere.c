#include "sphere.h"
#include "common.h"
#include "hittable.h"
#include <math.h>
bool sphere_hit(sphere s, ray r, interval ray_t, hit_record *rec) {
  vec3 orign_sub_center = sub_vec(r.origin, s.center);
  double a = dot(r.direction, r.direction);
  double b = dot(r.direction, orign_sub_center);
  double c = dot(orign_sub_center, orign_sub_center) - (s.radius * s.radius);
  double discriminant = (b * b) - (a * c);
  if (discriminant < 0) {
    return false;
  }
  double sqrt_discriminant = sqrt(discriminant);
  double root = (-b - sqrt_discriminant) / a;
  if (!surrounds(ray_t, root)) {
    root = (-b + sqrt_discriminant) / a;
    if (!surrounds(ray_t, root)) {
      return false;
    }
  }
  rec->t = root;
  rec->p = at(r, rec->t);
  rec->mat = s.mat;
  vec3 outward_normal =
      unit_vector(scalar_div(sub_vec(rec->p, s.center), s.radius));
  set_face_normal(rec, r, outward_normal);
  return true;
}
