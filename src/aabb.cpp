#include "aabb.h"
#include <fenv.h>

AABB::AABB() {}

AABB::AABB(const Vec3f &a, const Vec3f &b) : min_{a}, max_{b}, centroid_{((a + b) * 0.5)} {}

Vec3f AABB::min() const { return min_; }

Vec3f AABB::max() const { return max_; }

Vec3f AABB::centroid() const { return centroid_; }

bool AABB::intersect(const Ray &ray, float t_min, float t_max) const
{
    //fedisableexcept(FE_INVALID | FE_DIVBYZERO);

    for (int i = 0; i < 3; i++)
    {
        float invD = 1.0f / ray.direction_[i];

        float t0 = (min_[i] - ray.origin_[i]) * invD;
        float t1 = (max_[i] - ray.origin_[i]) * invD;

        if (invD < 0.0f)
            std::swap(t0, t1);

        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;

        if (t_max < t_min)
        {
            //feenableexcept(FE_INVALID | FE_DIVBYZERO);
            return false;
        }
    }
    //feenableexcept(FE_INVALID | FE_DIVBYZERO);
    return true;
}

AABB AABB::surroundingBox(const AABB &box_0, const AABB &box_1)
{
    Vec3f small = Vec3f(fmin(box_0.min()[0], box_1.min()[0]),
                        fmin(box_0.min()[1], box_1.min()[1]),
                        fmin(box_0.min()[2], box_1.min()[2]));

    Vec3f big = Vec3f(fmax(box_0.max()[0], box_1.max()[0]),
                      fmax(box_0.max()[1], box_1.max()[1]),
                      fmax(box_0.max()[2], box_1.max()[2]));

    return AABB(small - 0.001, big + 0.001);
}