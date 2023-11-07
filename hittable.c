#include "hittable.h"
#include "ray.h"
#include "vec3.h"
// outward normal must be unit length
void set_face_normal(hit_record *hit, ray r, vec3 outward_normal) {
  hit->front_face = dot(r.direction, outward_normal) < 0;
  if (hit->front_face) {
    hit->normal = outward_normal;
  } else {
    hit->normal = negate_vec(outward_normal);
  }
}
