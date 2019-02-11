#ifndef TRIANGLE_H
#define TRIANGLE_H

/*******************************************************************************
    Class Triangle:

  - Class that inherits the Primitive class. A triangle can be represented in 
    terms of it's three vertices and it's intersection algorithims are based on
    baricentric coordinates.

--------------------------------------------------------------------------------

  Variables:

  - const glm::vec3 v1_:
    - Holds the first triangle's vertice.

  - const glm::vec3 v2_:
    - Holds the first triangle's vertice.

  - const glm::vec3 v3_:
    - Holds the first triangle's vertice.


--------------------------------------------------------------------------------

  Methods:

  - Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3):
    - Constructor.

  - ~Triangle():
    - Deconstructor.

  - bool intersect(const Ray &ray, float t_min, float t_max, Record &record) const:
    - Caluclates ray-triangle intersection using an adapted version presented in 
      the paper "Fast, Minimum Storage Ray/Triangle Intersection" by Tomas Möller.

********************************************************************************/

#define TRIANGLE_WALD

#include "primitive.h"

class Triangle : public Primitive
{
public:
  Triangle(const glm::vec3 &v1,
           const glm::vec3 &v2,
           const glm::vec3 &v3);
  ~Triangle();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  const glm::vec3 v1_;
  const glm::vec3 v2_;
  const glm::vec3 v3_;

#ifdef TRIANGLE_WALD
  const int modulo[5] = {0, 1, 2, 0, 1};

  float normal_u;
  float normal_v;
  float normal_d;
  int k;

  float edge1_nu;
  float edge1_nv;
  float edge1_d;

  float edge2_nu;
  float edge2_nv;
  float edge2_d;

#endif
};

#endif