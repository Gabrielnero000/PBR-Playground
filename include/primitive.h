#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>
#include "ray.h"
#include "record.h"

class Primitive
{
public:
  typedef std::unique_ptr<Primitive> PrimitiveUniquePtr;
  Primitive();
  virtual ~Primitive();
  virtual bool intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const = 0;
};

#endif