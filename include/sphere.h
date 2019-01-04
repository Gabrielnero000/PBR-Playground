#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive
{
public:
  Sphere(const glm::vec3 &center,
         const float radius);

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  glm::vec3 center_;
  const float radius_;
};

#endif