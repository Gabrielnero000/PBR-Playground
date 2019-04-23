#ifndef AABB_H
#define AABB_H

#include "ray.h"

class AABB
{
  public:
    AABB();
    AABB(const Vec3f &a, const Vec3f &b);

    Vec3f min() const;
    Vec3f max() const;

    bool hit(const Ray &ray, float t_min, float t_max) const;

  private:

    Vec3f min_;
    Vec3f max_;
};

#endif