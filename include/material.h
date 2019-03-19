#ifndef MATERIAL_H
#define MATERIAL_H

#include "record.h"
#include "ray.h"
#include "onb.h"

class Material
{
public:
  Material(const glm::vec3 &emmiter);
  ~Material();
  virtual glm::vec3 directionGenerator() const = 0;
  virtual glm::vec3 BRDF(const glm::vec3 &w_in, const glm::vec3 &w_out) const = 0;

  glm::vec3 emmiter_;
};

#endif