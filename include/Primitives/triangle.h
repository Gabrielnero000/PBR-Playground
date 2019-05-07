#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"

class Triangle : public Primitive
{
public:
  Triangle(Material::MaterialPtr material,
           const std::string &id,
           const Vec3f &v1,
           const Vec3f &v2,
           const Vec3f &v3,
           const Vec3f &normal_v1,
           const Vec3f &normal_v2,
           const Vec3f &normal_v3,
           const bool smooth);
  ~Triangle();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  bool boundingBox(AABB &box) const;

  const Vec3f v1_;
  const Vec3f v2_;
  const Vec3f v3_;

  const Vec3f normal_;
  const Vec3f n1_;
  const Vec3f n2_;
  const Vec3f n3_;

  bool smooth_;

  const int modulo[5] = {0, 1, 2, 0, 1};

  float normal_u;
  float normal_v;
  float normal_d;
  int k;

  float B_nu;
  float B_nv;

  float C_nu;
  float C_nv;
};

#endif