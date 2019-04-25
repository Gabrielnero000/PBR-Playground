#pragma once

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>
#include "ray.h"
#include "record.h"
#include "material.h"
#include "aabb.h"

class Primitive
{
public:

  Material* material_;

  Primitive();
  Primitive(Material* material);
  virtual ~Primitive();
  virtual bool intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const = 0;
  virtual bool boundingBox(float t0,
                           float t1,
                           AABB &box) const = 0;
};

#endif