#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "material.h"

class Diffuse : public Material
{
public:
  Diffuse(Texture::TexturePtr texture);
  ~Diffuse();

  bool scatter(const Ray &w_in,
               const Record &record,
               Vec3f &attenuation,
               Ray &w_out) const;

  Material *duplicate() const override
  {
    return new Diffuse(Texture::TexturePtr(texture_->duplicate()));
  }
};

#endif