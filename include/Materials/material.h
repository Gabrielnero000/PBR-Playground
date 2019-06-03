#ifndef MATERIAL_H
#define MATERIAL_H

#include <random>
#include "Textures/texture.h"
#include "Utils/record.h"
#include "Utils/ray.h"
#include "Utils/onb.h"

class Material
{
public:
  typedef std::unique_ptr<Material> MaterialPtr;

  Material(Texture::TexturePtr texture);
  ~Material();

  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const = 0;

  virtual Material *duplicate() const = 0;

  virtual Vec3f emmiter(const float u, const float v, Vec3f &p) const;

  Vec3f random_in_sphere() const;
  Vec3f reflect(const Vec3f &v, const Vec3f &n) const;

  Texture::TexturePtr texture_;
};

#endif