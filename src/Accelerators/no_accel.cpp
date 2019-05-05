#include "Accelerators/no_accel.h"

NoAccel::NoAccel(std::vector<Primitive::PrimitivePtr> &primitives) : Accelerator::Accelerator(primitives) {}

NoAccel::~NoAccel() {}

void NoAccel::build() { return; }

bool NoAccel::trace(const Ray &ray,
                    float t_min,
                    float t_max,
                    Record &record) const
{
    bool intersected = false;
    Record tmp_record;
    float closest_so_far = t_max;

    // for each primitive
    for (std::size_t i = 0; i < primitives_.size(); i++)
    {
        if (primitives_[i]->intersect(ray, t_min, closest_so_far, tmp_record))
        {
            intersected = true;             // has intersection
            record = tmp_record;            // update intersection's record
            closest_so_far = tmp_record.t_; // update t_max
            record.index_ = i;              // the primitive index
        }
    }

    return intersected;
}