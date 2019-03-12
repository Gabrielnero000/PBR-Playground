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
  virtual Ray scatter(const Ray &r_in,
                      Record &record,
                      glm::vec3 &attenuation) const = 0;

  glm::vec3 emmiter_;
  ONB onb_;
};

#endif