#include "lambertian.h"

Lambertian::Lambertian(glm::vec3 &emmiter,
                       glm::vec3 &albedo) : Material::Material{emmiter},
                                            albedo_{albedo} {}

Lambertian::~Lambertian() {}

glm::vec3 Lambertian::directionGenerator() const
{
    glm::vec3 vec;

    do
    {
        vec = 2.0f * glm::vec3{drand48(), drand48(), drand48()} - glm::vec3{1, 1, 1};
    } while (glm::length(vec) >= 1.0f);

    return vec;
}

bool Lambertian::BRDF(const Ray &r_in,
                      const Record &record,
                      glm::vec3 &attenuation,
                      Ray &r_out) const
{
    const glm::vec3 target = record.point_ + record.normal_ + directionGenerator();
    r_out = Ray(record.point_, target - record.point_);
    attenuation = albedo_;
    return true;
}