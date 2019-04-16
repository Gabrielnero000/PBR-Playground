#ifndef TRIANGLE_H
#define TRIANGLE_H

#define TRIANGLE_FAST

#include "primitive.h"

class Triangle : public Primitive
{
public:
  Triangle(MaterialUniquePtr material,
           const Vec3f &v1,
           const Vec3f &v2,
           const Vec3f &v3);
  ~Triangle();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  const Vec3f v1_;
  const Vec3f v2_;
  const Vec3f v3_;
  const Vec3f normal_;

#ifdef TRIANGLE_FAST
  const int modulo[5] = {0, 1, 2, 0, 1};

  float normal_u;
  float normal_v;
  float normal_d;
  int k;

  float B_nu;
  float B_nv;

  float C_nu;
  float C_nv;

#endif
};

#endif