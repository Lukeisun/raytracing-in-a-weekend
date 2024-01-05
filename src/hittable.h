#ifndef HITTABLE_H
#define HITTABLE_H
#include "common.h"
#include "material.h"
typedef struct hit_record {
  vec3 p;
  vec3 normal;
  double t;
  bool front_face;
  material mat;
} hit_record;
void set_face_normal(hit_record *hit, ray r, vec3 outward_normal);

bool scatter_metal(material *mat, ray *r_in, hit_record *rec, vec3 *attenuation,
                   ray *scattered);
bool scatter_lambertian(material *mat, ray *r_in, hit_record *rec,
                        vec3 *attenuation, ray *scattered);
bool scatter_dielectric(material *mat, ray *r_in, hit_record *rec,
                        vec3 *attenuation, ray *scattered);
bool scatter(material *mat, ray *r_in, hit_record *rec, vec3 *attenuation,
             ray *scattered);
#endif
