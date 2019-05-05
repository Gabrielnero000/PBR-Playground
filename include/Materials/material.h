#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <random>
#include "Utils/record.h"
#include "Utils/ray.h"
#include "Utils/onb.h"

class Material
{
public:
  typedef std::unique_ptr<Material> MaterialPtr;

  Material(const Vec3f &emmiter, const Vec3f &albedo);
  ~Material();
  virtual bool scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const = 0;

  Vec3f random_in_sphere() const;
  Vec3f reflect(const Vec3f &v, const Vec3f &n) const;

  Vec3f emmiter_;
  Vec3f albedo_;
};

#endif