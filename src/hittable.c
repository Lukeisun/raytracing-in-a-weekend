#include "hittable.h"
#include "common.h"
#include "material.h"
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
bool scatter_lambertian(material *mat, __attribute__((unused)) ray *r_in,
                        hit_record *rec, vec3 *attenuation, ray *scattered) {
  vec3 scatter_direction = add_vec(rec->normal, random_unit_vector());
  if (near_zero(&scatter_direction)) {
    scatter_direction = rec->normal;
  }
  *scattered = (ray){rec->p, scatter_direction};
  *attenuation = mat->albedo;
  return true;
}
static double reflectance(double cosine, double ref_idx) {
  double r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}
bool scatter_dielectric(material *mat, ray *r_in, hit_record *rec,
                        vec3 *attenuation, ray *scattered) {
  double refraction_ratio = rec->front_face ? (1.0 / mat->ir) : mat->ir;
  vec3 unit_dir = unit_vector(r_in->direction);
  double cos_theta = fmin(dot(negate_vec(unit_dir), rec->normal), 1.0);
  double sin_theta = sqrt(1.0 - (cos_theta * cos_theta));
  bool cannot_refract = (refraction_ratio * sin_theta) > 1.0;
  vec3 direction;
  if (cannot_refract ||
      reflectance(cos_theta, refraction_ratio) > random_double()) {
    direction = reflect_vec(unit_dir, rec->normal);
  } else {
    direction = refract_vec(unit_dir, rec->normal, refraction_ratio);
  }
  *attenuation = (vec3){1.0, 1.0, 1.0};
  *scattered = (ray){rec->p, direction};
  return true;
}
bool scatter_metal(material *mat, ray *r_in, hit_record *rec, vec3 *attenuation,
                   ray *scattered) {
  vec3 unit_dir = unit_vector(r_in->direction);
  vec3 reflected = reflect_vec(unit_dir, rec->normal);
  *attenuation = mat->albedo;
  *scattered = (ray){
      rec->p, add_vec(reflected, scalar_mult(random_unit_vector(), mat->fuzz))};
  return (dot(scattered->direction, rec->normal) > 0);
}
bool scatter(material *mat, ray *r_in, hit_record *rec, vec3 *attenuation,
             ray *scattered) {
  switch (mat->material) {
  case LAMBERTIAN:
    return scatter_lambertian(mat, r_in, rec, attenuation, scattered);
  case METAL:
    return scatter_metal(mat, r_in, rec, attenuation, scattered);
  case DIELECTRIC:
    return scatter_dielectric(mat, r_in, rec, attenuation, scattered);
  default:
    printf("%d\n", mat->material);
    printf("Unknown material type\n");
    exit(1);
  }
}
