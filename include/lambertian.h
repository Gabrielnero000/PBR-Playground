#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material
{
public:
  Lambertian(glm::vec3 &emmiter, glm::vec3 &albedo);
  ~Lambertian();

  virtual glm::vec3 directionGenerator() const;
  virtual Ray scatter(const Ray &r_in,
                      const Record &record,
                      glm::vec3 &attenuation);

  glm::vec3 albedo_;
};

#endif