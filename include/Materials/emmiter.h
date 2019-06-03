#ifndef EMMITER_H
#define EMMITER_H

#include "material.h"

class Emmiter : public Material
{
public:
  Emmiter(Texture::TexturePtr texture, const float strength);
  ~Emmiter();

  bool scatter(const Ray &w_in,
               const Record &record,
               Vec3f &attenuation,
               Ray &w_out) const;

  Material *duplicate() const override
  {
    return new Emmiter(Texture::TexturePtr(texture_->duplicate()), strength_);
  }

  Vec3f emmiter(const float u, const float v, Vec3f &p) const;
  float strength_;
};

#endif