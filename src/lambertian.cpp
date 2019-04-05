#include "lambertian.h"

Lambertian::Lambertian(glm::vec3 &emmiter,
                       glm::vec3 &albedo) : Material::Material{emmiter},
                                            albedo_{albedo} {}

Lambertian::~Lambertian() {}

bool Lambertian::scatter(const Ray &w_in,
                         const Record &record,
                         glm::vec3 &attenuation,
                         Ray &w_out) const
{
    glm::vec3 random;
    do
    {
        random = 2.0f * glm::vec3{drand48(), drand48(), drand48()} - glm::vec3{1.0f, 1.0f, 1.0f};
    } while (random[0] * random[0] + random[1] * random[1] + random[2] * random[2] > 1.0f);

    glm::vec3 r_direction = record.point_ + record.normal_ + random;
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), glm::normalize(r_direction - record.point_));
    attenuation = 2.0f * albedo_ * glm::dot(w_out.direction_, record.normal_);

    return true;
}