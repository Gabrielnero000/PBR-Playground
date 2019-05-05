#ifndef SPECULAR_H
#define SPECULAR_H

#include "material.h"

class Specular : public Material
{
  public:
    Specular(const Vec3f &emmiter, const Vec3f &albedo, const float fuzz_factor);
    ~Specular();

    virtual bool scatter(const Ray &w_in,
                         const Record &record,
                         Vec3f &attenuation,
                         Ray &w_out) const;

    float fuzz_factor_;
};

#endif