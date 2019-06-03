#ifndef PERLIN_H
#define PERLIN_H

#include "texture.h"

class PerlinAux
{
public:
  float noise(const Vec3f &p) const;
  float turb(const Vec3f &p, int depth) const;

  static Vec3f *ranvec_;
  static int *perm_x_;
  static int *perm_y_;
  static int *perm_z_;
};

class Perlin : public Texture
{
public:
  Perlin(const float scale);
  ~Perlin();
  Vec3f value(const float u, const float v, const Vec3f &p) const;

  Texture *duplicate() const override
  {
    return new Perlin(*this);
  }

  PerlinAux noise_;
  float scale_;
};

#endif