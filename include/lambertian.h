#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material
{
public:
  Lambertian(Vec3f &emmiter, Vec3f &albedo);
  ~Lambertian();

  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const;

  Vec3f albedo_;
};

#endif