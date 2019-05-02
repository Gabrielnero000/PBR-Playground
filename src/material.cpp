#include "material.h"

Material::Material(const Vec3f &emmiter) : emmiter_{emmiter} {}

Material::~Material() {}

Vec3f Material::random_in_sphere() const
{
    std::minstd_rand gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    Vec3f random;
    do
    {
        random = 2.0f * Vec3f(dist(gen), dist(gen), dist(gen)) - 1.0f;
    } while (random.squared_lenght() > 1.0f);

    return random;
}