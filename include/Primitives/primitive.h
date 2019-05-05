#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Materials/material.h"
#include "Utils/aabb.h"

class Primitive
{
public:
  typedef std::unique_ptr<Primitive> PrimitivePtr;

  Primitive(Material::MaterialPtr material, const std::string &id);
  virtual ~Primitive();
  virtual bool intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const = 0;
  virtual bool boundingBox(AABB &box) const = 0;

  Material::MaterialPtr material_;
  const std::string id_;
};

#endif