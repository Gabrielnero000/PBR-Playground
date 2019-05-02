#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include <vector>
#include "primitive.h"

class Accelerator
{
  public:
    Accelerator(std::vector<Primitive::PrimitivePtr> &primitives);
    virtual ~Accelerator();

    virtual void build() = 0;

    virtual bool trace(const Ray &ray,
                       float t_min,
                       float t_max,
                       Record &record) const = 0;

    std::vector<Primitive::PrimitivePtr> &primitives_;
};

#endif