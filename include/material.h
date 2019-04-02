#ifndef MATERIAL_H
#define MATERIAL_H

#include "record.h"
#include "ray.h"
#include "onb.h"

class Material
{
public:
  Material(const glm::vec3 &emmiter_);
  ~Material();
  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       glm::vec3 &attenuation,
                       Ray &w_out) const = 0;

  glm::vec3 emmiter_;
};

#endif