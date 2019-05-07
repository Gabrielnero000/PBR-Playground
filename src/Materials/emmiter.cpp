#include "Materials/emmiter.h"

Emmiter::Emmiter(const Vec3f &emmiter,
                 const Vec3f &albedo) : Material::Material(emmiter, albedo) {}

Emmiter::~Emmiter() {}

bool Emmiter::scatter(const Ray &w_in,
                      const Record &record,
                      Vec3f &attenuation,
                      Ray &w_out) const
{
    return false;
}