#ifndef NO_ACCEL_H
#define NO_ACCEL_H

#include "accelerator.h"

class NoAccel : public Accelerator
{
public:
  NoAccel(std::vector<Primitive::PrimitivePtr> &primitives);
  ~NoAccel();

  void build();

  bool trace(const Ray &ray,
             float t_min,
             float t_max,
             Record &record) const;
};

#endif