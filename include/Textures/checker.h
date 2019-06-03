#ifndef CHECKER_H
#define CHECKER_H

#include "texture.h"

class Checker : public Texture
{
public:
  Checker(TexturePtr odd, TexturePtr even);
  ~Checker();
  Vec3f value(const float u, const float v, const Vec3f &p) const;

  Texture *duplicate() const override
  {
    return new Checker(TexturePtr(odd_->duplicate()), TexturePtr(even_->duplicate()));
  }

  TexturePtr odd_;
  TexturePtr even_;
};

#endif