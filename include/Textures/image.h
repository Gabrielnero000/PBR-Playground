#ifndef IMAGE_H
#define IMAGE_H

#include "texture.h"

class Image : public Texture
{
public:
  Image(unsigned char *pixels, int A, int B);
  ~Image();
  Vec3f value(const float u, const float v, const Vec3f &p) const;

  Texture *duplicate() const override
  {
    return new Image(*this);
  }

  unsigned char *data_;
  int nx_, ny_;
};

#endif