#ifndef MIX_H
#define Mix_H

#include "material.h"
#include <functional>

class Mix : public Material
{
  public:
    Mix(MaterialPtr material_1,
        MaterialPtr material_2,
        float value);
    ~Mix();

    bool scatter(const Ray &w_in,
                 const Record &record,
                 Vec3f &attenuation,
                 Ray &w_out) const;

    Material *duplicate() const override
    {
        return new Mix(MaterialPtr(material_1_->duplicate()), MaterialPtr(material_2_->duplicate()), value_);
    }

    MaterialPtr material_1_;
    MaterialPtr material_2_;

    float value_;
};

#endif