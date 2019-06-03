#ifndef COLOR_H
#define COLOR_H

#include "texture.h"

class Color : public Texture
{
public:
  Color(const Vec3f &color_);
  ~Color();
  Vec3f value(const float u, const float v, const Vec3f &p) const;

  Texture *duplicate() const override
  {
    return new Color(*this);
  }

  Vec3f color_;
};

#endif