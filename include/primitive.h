#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>
#include "ray.h"
#include "record.h"
#include "material.h"

class Primitive
{
public:
  typedef std::unique_ptr<Primitive> PrimitiveUniquePtr;
  typedef std::unique_ptr<Material> MaterialUniquePtr;

  MaterialUniquePtr material_;

  Primitive(MaterialUniquePtr material);
  virtual ~Primitive();
  virtual bool intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const = 0;
};

#endif