#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material
{
public:
  Lambertian(glm::vec3 &emmiter, glm::vec3 &albedo);
  ~Lambertian();

  virtual glm::vec3 directionGenerator() const;
  virtual glm::vec3 BRDF(const glm::vec3 &w_in, const glm::vec3 &w_out) const;

  glm::vec3 albedo_;
};

#endif