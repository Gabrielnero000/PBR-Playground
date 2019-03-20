#ifndef SCENE_H
#define SCENE_H

/*******************************************************************************
    Class Scene:

  - Class that represents the scene to be rendered. Basically, holds an
    reference to primitives and calls the intersection method of each one of
    them.

--------------------------------------------------------------------------------

  Variables:

  - std::vector<Primitive::PrimitiveUniquePtr> primitives_:
    - Holds references to each primitive in the scene.

--------------------------------------------------------------------------------

  Methods:

  - Scene():
    - Constructor.

  - ~Scene():
    - Deconstructor. 'Virtual' because it's an abstract class.

  - bool intersect(const Ray &ray, float t_min, float t_max, Record &record) const;
    - Calls the intersection's method of each primitive stored.

********************************************************************************/

#include <vector>
#include "primitive.h"
#include "sphere.h"
#include "triangle.h"
#include "mesh.h"
#include "material.h"
#include "lambertian.h"

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