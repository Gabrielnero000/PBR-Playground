#pragma once

#ifndef BVH_H
#define BVH_H

#include "accelerator.h"

class BVH : public Accelerator
{
public:
  class BVHNode
  {
  public:
    BVHNode(const std::vector<int> primitive_indexes, const AABB box);
    ~BVHNode();

    BVHNode *left_;
    BVHNode *right_;

    const std::vector<int> primitive_indexes_;
    AABB box_;
  };

  BVH(std::vector<Primitive::PrimitivePtr> &primitives);
  ~BVH();

  void build();

  BVHNode *buildRecursive(std::vector<int> primitive_indexes);

  bool trace(const Ray &ray,
             float t_min,
             float t_max,
             Record &record) const;

  bool traceRecursive(const Ray &ray,
                      float t_min,
                      float &t_max,
                      Record &record,
                      BVHNode *node) const;

  std::vector<int> primitive_indexes_;
  BVHNode *root_;
};

#endif