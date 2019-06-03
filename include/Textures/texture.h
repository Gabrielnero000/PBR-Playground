#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include "Utils/vec.h"

class Texture
{
public:
  typedef std::unique_ptr<Texture> TexturePtr;

  Texture();
  ~Texture();
  virtual Vec3f value(const float u, const float v, const Vec3f &p) const = 0;

  virtual Texture *duplicate() const = 0;
};

#endif