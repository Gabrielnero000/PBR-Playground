#include "lambertian.h"

Lambertian::Lambertian(Vec3f &emmiter,
                       Vec3f &albedo) : Material::Material{emmiter},
                                        albedo_{albedo} {}

Lambertian::~Lambertian() {}

bool Lambertian::scatter(const Ray &w_in,
                         const Record &record,
                         Vec3f &attenuation,
                         Ray &w_out) const
{

    std::minstd_rand gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    Vec3f random;
    do
    {
        random = 2.0f * Vec3f(dist(gen), dist(gen), dist(gen)) - 1.0f;
    } while (random.squared_lenght() > 1.0f);

    Vec3f r_direction = record.point_ + record.normal_ + random;
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), (r_direction - record.point_).as_unit());
    attenuation = 2.0f * albedo_ * w_out.direction_.dot(record.normal_);

    return true;
}