#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "primitive.h"
#include "sphere.h"

class Scene
{
public:
  Scene();
  ~Scene();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;
  void load();

  std::vector<Primitive::PrimitiveUniquePtr> primitives_;
};

#endif