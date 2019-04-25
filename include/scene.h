#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "primitive.h"

class Scene : public Primitive
{
public:
  Scene();

  Scene(Primitive** primitives, int size);

  ~Scene();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  bool boundingBox(float t0,
                   float t1,
                   AABB &box) const;
  Primitive load();

  Primitive **primitives_;
  int size_;
};

#endif