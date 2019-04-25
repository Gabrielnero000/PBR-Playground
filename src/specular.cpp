#include "specular.h"

Specular::Specular(const Vec3f &emmiter,
                   const Vec3f &albedo) : Material::Material{emmiter},
                                          albedo_{albedo} {}

Specular::~Specular() {}

bool Specular::scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const
{
    Vec3f r_direction = w_in.direction_ - 2.0f * record.normal_ * w_in.direction_.dot(record.normal_);
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), r_direction.as_unit());
    attenuation = albedo_;
    return true;
}