#include "Materials/diffuse.h"

Diffuse::Diffuse(Texture::TexturePtr texture) : Material::Material(std::move(texture)) {}

Diffuse::~Diffuse() {}

bool Diffuse::scatter(const Ray &w_in,
                      const Record &record,
                      Vec3f &attenuation,
                      Ray &w_out) const
{

    Vec3f r_direction = record.point_ + record.normal_ + Material::random_in_sphere();
    w_out = Ray(record.point_ + (record.normal_ * 0.0001f), (r_direction - record.point_).as_unit());
    attenuation = texture_->value(record.u_, record.v_, record.point_); // ;

    return true;
}
