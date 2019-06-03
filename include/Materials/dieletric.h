#ifndef DIELETRIC_H
#define DIELETRIC_H

#include "material.h"

bool refract(const Vec3f &v,
             const Vec3f &n,
             float ni_over_nt,
             Vec3f &refracted);

float schlick(float cosine, float ref_idx);

class Dieletric : public Material
{
public:
  Dieletric(Texture::TexturePtr texture,
            const float ref_idx);
  ~Dieletric();

  bool scatter(const Ray &w_in,
               const Record &record,
               Vec3f &attenuation,
               Ray &w_out) const;
  Material *duplicate() const override
  {
    return new Dieletric(Texture::TexturePtr(texture_->duplicate()), ref_idx_);
  }
  float ref_idx_;
};

#endif