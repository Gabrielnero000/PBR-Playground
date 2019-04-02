#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material
{
public:
  Lambertian(glm::vec3 &emmiter, glm::vec3 &albedo);
  ~Lambertian();

  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       glm::vec3 &attenuation,
                       Ray &w_out) const;

  glm::vec3 albedo_;
};

#endif