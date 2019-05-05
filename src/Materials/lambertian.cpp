#include "Materials/lambertian.h"

Lambertian::Lambertian(const Vec3f &emmiter,
                       const Vec3f &albedo) : Material::Material(emmiter, albedo) {}

Lambertian::~Lambertian() {}

bool Lambertian::scatter(const Ray &w_in,
                         const Record &record,
                         Vec3f &attenuation,
                         Ray &w_out) const
{

    Vec3f r_direction = record.point_ + record.normal_ + Material::random_in_sphere();
    w_out = Ray(record.point_ + (record.normal_ * 0.001f), (r_direction - record.point_).as_unit());
    attenuation = albedo_ * w_out.direction_.dot(record.normal_);

    return true;
}