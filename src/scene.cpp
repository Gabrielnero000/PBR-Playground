#include "scene.h"

Scene::Scene() {}

Scene::Scene(Primitive **primitives, int size) : primitives_{primitives},
                                                 size_{size} {}

Scene::~Scene() {}

bool Scene::intersect(const Ray &ray,
                      float t_min,
                      float t_max,
                      Record &record) const
{
    bool intersected = false;
    Record tmp_record;
    float closest_so_far = t_max;

    // for each primitive
    for (int i = 0; i < size_; i++)
    {
        if (primitives_[i]->intersect(ray, t_min, closest_so_far, tmp_record))
        {
            intersected = true;             // has intersection
            record = tmp_record;            // update intersection's record
            closest_so_far = tmp_record.t_; // update t_max
        }
    }

    return intersected;
}

bool Scene::boundingBox(float t0,
                        float t1,
                        AABB &box) const
{
    if (size_ < 1)
        return false;

    AABB temp_box;
    bool first_true = primitives_[0]->boundingBox(t0, t1, temp_box);

    if (!first_true)
        return false;
    else
        box = temp_box;

    for (int i = 1; i < size_; i++)
    {
        if (primitives_[0]->boundingBox(t0, t1, temp_box))
            box = AABB::surroundingBox(box, temp_box);
        else
            return false;
    }
    return true;
}