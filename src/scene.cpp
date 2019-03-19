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
    float closest_so_far = t_max;

    // for each primitive
    for (std::size_t i = 0; i < primitives_.size(); i++)
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

// Just for some tests
void Scene::load()
{
    // Scene 1 - Spheres

    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{-0.5f, 0.0f, -1.0f}, 0.2f}));
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, -0.5f, -2.0f}, 0.2f}));
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, 0.5f, -3.0f}, 0.2f}));

    // Scene 2 - Triangles

    /*for (int i = 1; i <= 2; i++)
    {
        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{glm::vec3{0.0f, 0.0f, -1.0f},
                                                                         glm::vec3{1.0f, 0.0f, -1.0f},
                                                                         glm::vec3{0.0f, 1.0f, -1.0f}}));
    }*/

    // Scene 3 - Suzzy
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Mesh{"monkey.obj"}));

    // Scene 4 - Sphere and plane
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, 0.0f, -1.0f}, 0.5f}));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, -100.5f, -1.0f}, 100.0f}));

    // Scene 5 - Box with sphere
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, -0.8f, 0.0f}, 0.2f}));
    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.0f, 1.0f, 0.0f}, 0.2f}));

    //primitives_.push_back(Primitive::PrimitiveUniquePtr(new Mesh{"box.obj"}));
}