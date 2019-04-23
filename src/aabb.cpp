#include "aabb.h"

AABB::AABB() {}

AABB::AABB(const Vec3f &a, const Vec3f &b) : min_{a}, max_{b} {}

Vec3f AABB::min() const { return min_; }

Vec3f AABB::max() const { return max_; }

bool AABB::hit(const Ray &ray, float t_min, float t_max) const
{
    for (int i = 0; i < 3; i++)
    {
        const float inv_dir = -1.0f / ray.direction_[i];

        float t0 = (min()[i] - ray.origin_[i]) * inv_dir;
        float t1 = (max()[i] - ray.origin_[i]) * inv_dir;

        if (inv_dir < 0.0f)
            std::swap(t0, t1);

        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;

        if (t_max <= t_min)
            return false;
    }
    return true;
}