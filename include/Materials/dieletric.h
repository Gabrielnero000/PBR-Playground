#ifndef DIELETRIC_H
#define DIELETRIC_H

#include "material.h"

bool refract(const Vec3f &v,
             const Vec3f &n,
             float ni_over_nt,
             Vec3f &refracted);

float schlick(float cosine, float ref_idx);

class Dieletric : public Material
{
public:
  Dieletric(const Vec3f &emmiter,
            const Vec3f &albedo,
            const float ref_idx);
  ~Dieletric();

  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const;
  ;

  float ref_idx_;
};

#endif