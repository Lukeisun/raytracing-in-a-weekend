#include "hittable.h"
#include "common.h"
// outward normal must be unit length
void set_face_normal(hit_record *hit, ray r, vec3 outward_normal) {
  hit->front_face = dot(r.direction, outward_normal) < 0;
  if (hit->front_face) {
    hit->normal = outward_normal;
  } else {
    hit->normal = negate_vec(outward_normal);
  }
}
bool scatter_lambertian(hit_record *rec, ray *scattered) {
  vec3 scatter_direction = add_vec(rec->normal, random_unit_vector());
  if (near_zero(&scatter_direction)) {
    scatter_direction = rec->normal;
  }
  *scattered = (ray){rec->p, scatter_direction};
  return true;
}
bool scatter_metal(ray *r_in, hit_record *rec, ray *scattered) {
  vec3 unit_dir = unit_vector(r_in->direction);
  vec3 reflected = reflect_vec(&unit_dir, &rec->normal);
  *scattered = (ray){rec->p, reflected};
  return true;
}
bool scatter(material *mat, ray *r_in, hit_record *rec, vec3 *attenuation,
             ray *scattered) {
  switch (mat->material) {
  case LAMBERTIAN:
    scatter_lambertian(rec, scattered);
    break;
  case METAL:
    scatter_metal(r_in, rec, scattered);
    break;
  default:
    printf("Unknown material type\n");
    exit(1);
  }
  attenuation = &mat->albedo;
}
