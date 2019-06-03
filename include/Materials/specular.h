#ifndef SPECULAR_H
#define SPECULAR_H

#include "material.h"

class Specular : public Material
{
public:
  Specular(Texture::TexturePtr texture, const float fuzz_factor);
  ~Specular();

  bool scatter(const Ray &w_in,
               const Record &record,
               Vec3f &attenuation,
               Ray &w_out) const;

  Material *duplicate() const override
  {
    return new Specular(Texture::TexturePtr(texture_->duplicate()), fuzz_factor_);
  }

  float fuzz_factor_;
};

#endif