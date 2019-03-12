#include "lambertian.h"

Lambertian::Lambertian(glm::vec3 &emmiter,
                       glm::vec3 &albedo) : Material::Material{emmiter},
                                            albedo_{albedo} {}

Lambertian::~Lambertian() {}

glm::vec3 Lambertian::directionGenerator() const
{
    const float theta = acos(1.0f - (float)drand48());
    const float phi = 2.0f * M_PI * (float)drand48();
    return onb_.inverse_ * glm::vec3{(float)sin(theta) * cos(phi),
                                     sin(theta) * sin(phi),
                                     cos(theta)};
}

Ray Lambertian::scatter(const Ray &r_in,
                        const Record &record,
                        glm::vec3 &attenuation)
{
    onb_.setFromV(record.normal_);
    attenuation = albedo_;
    return Ray(record.point_, directionGenerator());
}