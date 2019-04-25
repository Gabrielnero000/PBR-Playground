#pragma once

#ifndef BVH_H
#define BVH_H

#include "primitive.h"

class BVH : public Primitive
{
  public:
    BVH();
    BVH(Primitive **list, int n, float t0, float t1);

    ~BVH();

    bool intersect(const Ray &ray,
                   float t_min,
                   float t_max,
                   Record &record) const;

    bool boundingBox(float t0,
                     float t1,
                     AABB &box) const;

    Primitive* left_;
    Primitive* right_;
    AABB box_;
};

#endif