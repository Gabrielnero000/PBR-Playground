#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive
{
public:
  Sphere(Material::MaterialPtr material,
         const Vec3f &center,
         const float radius);

  ~Sphere();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  bool boundingBox(AABB &box) const;

  const Vec3f center_;
  const float radius_;
};

#endif