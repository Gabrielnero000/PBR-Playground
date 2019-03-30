#include "lambertian.h"

Lambertian::Lambertian(glm::vec3 &emmiter,
                       glm::vec3 &albedo) : Material::Material{emmiter},
                                            albedo_{albedo * (float)(1.0f / M_PI)} {}

Lambertian::~Lambertian() {}

glm::vec3 Lambertian::directionGenerator() const
{
    glm::vec3 p;
    do
    {
        p = 2.0f * glm::vec3{drand48(), drand48(), drand48()} - glm::vec3{1.0f, 1.0f, 1.0f};
    } while (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] >= 1.0f);
    return p;
}

glm::vec3 Lambertian::BRDF(const glm::vec3 &w_in, const glm::vec3 &w_out) const
{
    return albedo_;
}