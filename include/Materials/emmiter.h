#ifndef EMMITER_H
#define EMMITER_H

#include "material.h"

class Emmiter : public Material
{
public:
  Emmiter(const Vec3f &emmiter, const Vec3f &albedo);
  ~Emmiter();

  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const;
};

#endif