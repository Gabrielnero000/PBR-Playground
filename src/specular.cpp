#include "specular.h"

Specular::Specular(glm::vec3 &emmiter,
                   glm::vec3 &albedo) : Material::Material{emmiter},
                                        albedo_{albedo} {}

Specular::~Specular() {}

bool Specular::scatter(const Ray &w_in,
                       const Record &record,
                       glm::vec3 &attenuation,
                       Ray &w_out) const
{
    glm::vec3 r_direction = w_in.direction_ - 2.0f * record.normal_ * glm::dot(w_in.direction_, record.normal_);
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), glm::normalize(r_direction));
    attenuation = albedo_;
    return true; //glm::dot(w_out.direction_, record.normal_) > 0.0f;
}