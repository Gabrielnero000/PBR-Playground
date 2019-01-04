#include "scene.h"

Scene::Scene() {}

Scene::~Scene() {}

bool Scene::intersect(const Ray &ray,
                      float t_min,
                      float t_max,
                      Record &record) const
{
    bool intersected = false;
    Record tmp_record;
    std::size_t num_primitives = primitives_.size();
    float closest_so_far = t_max;

    for (std::size_t i = 0; i < num_primitives; i++)
        if (primitives_[i]->intersect(ray, t_min, closest_so_far, tmp_record))
        {
            intersected = true;
            record = tmp_record;
            closest_so_far = tmp_record.t_;
        }

    return intersected;
}

void Scene::load()
{
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{-0.5f, 0.0f, -1.0f}, 0.2f}));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, -0.5f, -2.0f}, 0.2f}));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, 0.5f, -3.0f}, 0.2f}));
}