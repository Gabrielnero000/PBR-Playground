#include "Materials/specular.h"

Specular::Specular(Texture::TexturePtr texture,
                   float fuzz_factor) : Material::Material(std::move(texture))
{
    fuzz_factor_ = fuzz_factor < 1.0f ? fuzz_factor : 1.0f;
}

Specular::~Specular() {}

bool Specular::scatter(const Ray &w_in,
                       const Record &record,
                       Vec3f &attenuation,
                       Ray &w_out) const
{
    Vec3f r_direction = reflect(w_in.direction_, record.normal_);
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), (r_direction + fuzz_factor_ * Material::random_in_sphere()).as_unit());
    attenuation = texture_->value(record.u_, record.v_, record.point_);
    return w_out.direction_.dot(record.normal_) > 0.0f;
}