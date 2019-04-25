#include "bvh.h"

// Util for x-axis comparation
int box_x_compare(const void *a, const void *b)
{
    AABB box_left, box_right;
    Primitive *a_h = *(Primitive **)a;
    Primitive *b_h = *(Primitive **)b;

    if (!a_h->boundingBox(0, 0, box_left) || !b_h->boundingBox(0, 0, box_right))
        std::cerr << "No bounding box in BVH constructor" << std::endl;

    if (box_left.min()[0] - box_right.min()[0] < 0.0f)
        return -1;
    else
        return 1;
}

// Util for y-axis comparation
int box_y_compare(const void *a, const void *b)
{
    AABB box_left, box_right;
    Primitive *a_h = *(Primitive **)a;
    Primitive *b_h = *(Primitive **)b;

    if (!a_h->boundingBox(0, 0, box_left) || !b_h->boundingBox(0, 0, box_right))
        std::cerr << "No bounding box in BVH constructor" << std::endl;

    if (box_left.min()[0] - box_right.min()[0] < 0.0f)
        return -1;
    else
        return 1;
}

// Util for z-axis comparation
int box_z_compare(const void *a, const void *b)
{
    AABB box_left, box_right;
    Primitive *a_h = *(Primitive **)a;
    Primitive *b_h = *(Primitive **)b;

    if (!a_h->boundingBox(0, 0, box_left) || !b_h->boundingBox(0, 0, box_right))
        std::cerr << "No bounding box in BVH constructor" << std::endl;

    if (box_left.min()[0] - box_right.min()[0] < 0.0f)
        return -1;
    else
        return 1;
}

BVH::BVH() : Primitive::Primitive(nullptr) {}

BVH::BVH(Primitive **list, int n, float t0, float t1) : Primitive::Primitive(nullptr)
{
    const int axis = int(3 * drand48());
    if (axis == 0)
        qsort(list, n, sizeof(Primitive *), box_x_compare);
    else if (axis == 1)
        qsort(list, n, sizeof(Primitive *), box_y_compare);
    else
        qsort(list, n, sizeof(Primitive *), box_z_compare);

    if (n == 1)
        left_ = right_ = list[0];
    else
    {
        left_ = new BVH(list, n / 2, t0, t1);
        right_ = new BVH(list + n / 2, n - n / 2, t0, t1);
    }
    AABB box_left, box_right;
    if (!left_->boundingBox(t0, t1, box_left) || !right_->boundingBox(t0, t1, box_right))
        std::cerr << "No bounding box in BVH constructor" << std::endl;
    box_ = AABB::surroundingBox(box_left, box_right);
}

BVH::~BVH() {}

bool BVH::intersect(const Ray &ray,
                    float t_min,
                    float t_max,
                    Record &record) const
{
    if (box_.intersect(ray, t_min, t_max))
    {
        Record left_rec, right_rec;

        bool hit_left = left_->intersect(ray, t_min, t_max, left_rec);
        bool hit_right = right_->intersect(ray, t_min, t_max, right_rec);

        if (hit_left && hit_right)
        {
            if (left_rec.t_ < right_rec.t_)
                record = left_rec;
            else
                record = right_rec;

            return true;
        }
        else if (hit_left)
        {
            record = left_rec;
            return true;
        }
        else if (hit_right)
        {
            record = right_rec;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool BVH::boundingBox(float t0, float t1, AABB &box) const
{
    box = box_;
    return true;
}