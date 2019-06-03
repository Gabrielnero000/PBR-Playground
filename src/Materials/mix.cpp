#include "Materials/mix.h"

Mix::Mix(MaterialPtr material_1,
         MaterialPtr material_2,
         float value) : Material::Material(nullptr),
                        material_1_(std::move(material_1)),
                        material_2_(std::move(material_2)),
                        value_(value) {}

bool Mix::scatter(const Ray &w_in,
                  const Record &record,
                  Vec3f &attenuation,
                  Ray &w_out) const
{
    std::minstd_rand gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    if (value_ < dist(gen))
        return material_1_->scatter(w_in, record, attenuation, w_out);
    else
        return material_2_->scatter(w_in, record, attenuation, w_out);
}