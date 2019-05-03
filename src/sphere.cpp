#include "sphere.h"

Sphere::Sphere(Material::MaterialPtr material,
               const std::string &id,
               const Vec3f &center,
               const float radius) : Primitive::Primitive(std::move(material), id),
                                     center_{center},
                                     radius_{radius} {}

Sphere::~Sphere() {}

bool Sphere::intersect(const Ray &ray,
                       float t_min,
                       float t_max,
                       Record &record) const
{
    float x1;
    float x2;

    Vec3f center_to_origin = ray.origin_ - center_;

    float a = ray.direction_.dot(ray.direction_);                         // dot(D, D)
    float b = center_to_origin.dot(ray.direction_);                       // dot(D, O-C)
    float c = center_to_origin.dot(center_to_origin) - radius_ * radius_; // dot(O-C, O-C) - R^2

    float disc = b * b - a * c; // Bhaskara's method

    if (disc > 0.0f) // Has inteserction
    {
        float temp = sqrt(disc);
        x1 = (-b - temp) / a;         // First zero
        if (x1 < t_max && x1 > t_min) // x1 is in [x_min, x_max]
        {
            record.t_ = x1;
            record.point_ = ray.evaluate(x1);
            record.normal_ = ((record.point_ - center_) / radius_).as_unit();
            return true;
        }
        // Same as x1
        x2 = (-b + temp) / a;
        if (x2 < t_max && x2 > t_min)
        {
            record.t_ = x2;
            record.point_ = ray.evaluate(x1);
            record.normal_ = ((record.point_ - center_) / radius_).as_unit();
            return true;
        }
    }
    return false; // No intersection
}

bool Sphere::boundingBox(AABB &box) const
{
    box = AABB();
    box.min_ = center_ - radius_;
    box.max_ = center_ + radius_;
    box.centroid_ = center_;
    return true;
}