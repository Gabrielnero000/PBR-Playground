#include "Materials/material.h"

Material::Material(Texture::TexturePtr texture) : texture_{std::move(texture)} {}

Material::~Material() {}

Vec3f Material::random_in_sphere() const
{
    std::minstd_rand gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    Vec3f random;
    do
    {
        random = 2.0f * Vec3f(dist(gen), dist(gen), dist(gen)) - 1.0f;
    } while (random.squared_lenght() >= 1.0f);

    return random;
}

Vec3f Material::reflect(const Vec3f &v, const Vec3f &n) const
{
    return v - 2.0f * n * v.dot(n);
}

Vec3f Material::emmiter(const float u, const float v, Vec3f &p) const
{
    return Vec3f(0.0f);
};