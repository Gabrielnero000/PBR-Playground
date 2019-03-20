#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

/*******************************************************************************
    Class Sphere:

  - Class that inherits the Primitive class. A sphere can be represented in 
    terms of it's center and radius and it's intersection algorithim is basically
    solve an 2nd-degree equation.

--------------------------------------------------------------------------------

  Variables:

  - const glm::vec3 center_:
    - Holds the sphere's center (and position).

  - const float radius_:
    -  Holds the sphere's radius.

--------------------------------------------------------------------------------

  Methods:

  - Primitive(const glm::vec3 &center, const float radius):
    - Constructor.

  - ~Sphere():
    - Deconstructor.

  - bool intersect(const Ray &ray, float t_min, float t_max, Record &record) const:
    - Caluclates ray-sphere intersection using an adapted version presented in 
      the book "Ray Tracing in one weekend" by Peter Shirley:

********************************************************************************/

class Sphere : public Primitive
{
public:
  Sphere(MaterialUniquePtr material,
         const glm::vec3 &center,
         const float radius);

  ~Sphere();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  const glm::vec3 center_;
  const float radius_;
};

#endif