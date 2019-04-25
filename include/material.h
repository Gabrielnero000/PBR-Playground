#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

struct Record;

#include "record.h"
#include "ray.h"
#include "onb.h"

class Material
{
public:
  Material(const Vec3f &emmiter_);
  ~Material();
  virtual bool scatter(const Ray &w_in,
                       Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const = 0;

  Vec3f emmiter_;
};

#endif