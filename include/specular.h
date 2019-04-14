#ifndef SPECULAR_H
#define SPECULAR_H

#include "material.h"

class Specular : public Material
{
  public:
    Specular(glm::vec3 &emmiter, glm::vec3 &albedo);
    ~Specular();

    virtual bool scatter(const Ray &w_in,
                         const Record &record,
                         glm::vec3 &attenuation,
                         Ray &w_out) const;

    glm::vec3 albedo_;
};

#endif