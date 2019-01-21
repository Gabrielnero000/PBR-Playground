#include "sphere.h"

Sphere::Sphere(const glm::vec3 &center,
               const float radius) : center_{center},
                                     radius_{radius} {}

Sphere::~Sphere() {}


/*  Solves the equation: 

        t^2 * dot(D, D) + 2*t * dot(D, O-C) + dot(O-C, O-C) - R^2 = 0

    where:  D is the ray direction
            O is the ray origin
            C is the sphere center
            t is the unknow parameter
*/
bool Sphere::intersect(const Ray &ray,
                       float t_min,
                       float t_max,
                       Record &record) const
{
    float x1;
    float x2;

    glm::vec3 center_to_origin = ray.origin_ - center_;

    float a = glm::dot(ray.direction_, ray.direction_); // dot(D, D)
    float b = glm::dot(center_to_origin, ray.direction_); // dot(D, O-C)
    float c = glm::dot(center_to_origin, center_to_origin) - radius_ * radius_; // dot(O-C, O-C) - R^2

    float disc = b * b - a * c; // Bhaskara's method

    if (disc > 0.0f) // Has inteserction
    {
        float temp = sqrt(disc);
        x1 = (-b - temp) / a; // First zero
        if (x1 < t_max && x1 > t_min) // x1 is in [x_min, x_max]
        {
            record.t_ = x1;
            record.point_ = ray.evaluate(x1);
            record.normal_ = (record.point_ - center_) / radius_;
            return true;
        }
        // Same as x1
        x2 = (-b + temp) / a;
        if (x2 < t_max && x2 > t_min)
        {
            record.t_ = x2;
            record.point_ = ray.evaluate(x1);
            record.normal_ = (record.point_ - center_) / radius_;
            return true;
        }
    }
    else
        return false; // No intersection
}