#include "sphere.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
bool sphere_hit(sphere s, ray r, double tmin, double tmax, hit_record *rec) {
  vec3 orign_sub_center = sub_vec(r.origin, s.center);
  double a = length(r.direction);
  double b = dot(r.direction, orign_sub_center);
  double c = length(orign_sub_center) - (s.radius * s.radius);
  double discriminant = (b * b) - (a * c);
  if (discriminant < 0) {
    return false;
  }
  double sqrt_discriminant = sqrt(discriminant);
  double root = (-b - sqrt_discriminant) / a;
  if (root <= tmin || tmax <= root) {
    root = (-b + sqrt_discriminant) / a;
    if (root <= tmin || tmax <= root) {
      return false;
    }
  }
  rec->t = root;
  rec->p = at(r, rec->t);
  vec3 outward_normal =
      unit_vector(scalar_div(sub_vec(rec->p, s.center), s.radius));
  set_face_normal(rec, r, outward_normal);
  return true;
}
