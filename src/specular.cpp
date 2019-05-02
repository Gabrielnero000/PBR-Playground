#include "specular.h"

Specular::Specular(Vec3f &emmiter,
                   Vec3f &albedo,
                   float fuzz_factor) : Material::Material{emmiter},
                                        albedo_{albedo}
{
    fuzz_factor_ = fuzz_factor < 1.0f ? fuzz_factor : 1.0f;
}

Specular::~Specular() {}

bool Specular::scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const
{
    Vec3f r_direction = w_in.direction_ - 2.0f * record.normal_ * w_in.direction_.dot(record.normal_);
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), (r_direction + fuzz_factor_ * Material::random_in_sphere()).as_unit());
    attenuation = albedo_;
    return w_out.direction_.dot(record.normal_) > 0.0f;
}