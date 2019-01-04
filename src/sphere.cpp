#include "sphere.h"

Sphere::Sphere(const glm::vec3 &center,
               const float radius) : center_{center},
                                     radius_{radius} {}

bool Sphere::intersect(const Ray &ray,
                       float t_min,
                       float t_max,
                       Record &record) const
{
    float x1;
    float x2;

    glm::vec3 center_to_origin = ray.origin_ - center_;

    float a = glm::dot(ray.direction_, ray.direction_);
    float b = glm::dot(center_to_origin, ray.direction_);
    float c = glm::dot(center_to_origin, center_to_origin) - radius_ * radius_;

    float disc = b * b - a * c;

    if (disc > 0.0f)
    {
        float temp = sqrt(disc);
        x1 = (-b - temp) / a;
        if (x1 < t_max && x1 > t_min)
        {
            record.t_ = x1;
            record.point_ = ray.evaluate(x1);
            record.normal_ = (record.point_ - center_) / radius_;
            return true;
        }
        x2 = (-b + temp) / a;
        if (x2 < t_max && x2 > t_min)
        {
            record.t_ = x2;
            record.point_ = ray.evaluate(x1);
            record.normal_ = (record.point_ - center_) / radius_;
            return true;
        }

        return true;
    }
    else
        return false;
}