#include "Materials/emmiter.h"

Emmiter::Emmiter(Texture::TexturePtr texture,
                 const float strength) : Material::Material(std::move(texture)),
                                         strength_(strength) {}

Emmiter::~Emmiter() {}

bool Emmiter::scatter(const Ray &w_in,
                      const Record &record,
                      Vec3f &attenuation,
                      Ray &w_out) const
{
    return false;
}

Vec3f Emmiter::emmiter(const float u, const float v, Vec3f &p) const
{
    return texture_->value(u, v, p) * strength_;
}
