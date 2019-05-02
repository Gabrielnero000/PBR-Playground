#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "material.h"
#include "aabb.h"

class Primitive
{
public:
  typedef std::unique_ptr<Primitive> PrimitivePtr;

  Material::MaterialPtr material_;

  Primitive(Material::MaterialPtr material);
  virtual ~Primitive();
  virtual bool intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const = 0;
  virtual bool boundingBox(AABB &box) const = 0;
};

#endif