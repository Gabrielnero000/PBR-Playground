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
            record.index_ = i;              // the primitive index
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
    /*glm::vec3 emmiter{0.0f, 0.0f, 0.0f};
    glm::vec3 albedo{0.8f, 0.8f, 0.8f};
    for (int i = 1; i <= 2; i++)
    {
        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter, albedo)),
                                                                         glm::vec3{0.0f, 0.0f, -1.0f},
                                                                         glm::vec3{1.0f, 0.0f, -1.0f},
                                                                         glm::vec3{0.0f, 1.0f, -1.0f}}));
    }*/

    // Scene 3 - Suzzy
    /*glm::vec3 emmiter{0.0f, 0.0f, 0.0f};
    glm::vec3 albedo{0.8f, 0.8f, 0.8f};
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Mesh{Primitive::MaterialUniquePtr(new Lambertian(emmiter, albedo)), "monkey.obj"}));*/

    // Scene 4 - Cornell Box
    /*glm::vec3 emmiter_1{0.0f, 0.0f, 0.0f};
    glm::vec3 albedo_1{0.5f, 0.5f, 0.5f};

    glm::vec3 emmiter_2{10.0f, 10.0f, 10.0f};
    glm::vec3 albedo_2{0.0f, 0.0f, 0.0f};

    glm::vec3 emmiter_3{0.0f, 0.0f, 0.0f};
    glm::vec3 albedo_3{0.85f, 0.05f, 0.05f};

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_3, albedo_3)),
                                                                   glm::vec3{-0.5f, -0.5f, 0.0f},
                                                                   0.5f}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter_2, albedo_2)),
                                                                     glm::vec3{-0.5f, 0.999f, -0.5f},
                                                                     glm::vec3{0.5f, 0.999f, 0.5f},
                                                                     glm::vec3{-0.5f, 0.999f, 0.5f}}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter_2, albedo_2)),
                                                                     glm::vec3{-0.5f, 0.999f, -0.5f},
                                                                     glm::vec3{0.5f, 0.999f, -0.5f},
                                                                     glm::vec3{0.5f, 0.999f, 0.5f}}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Mesh{Primitive::MaterialUniquePtr(new Lambertian(emmiter_1, albedo_1)),
                                                                 "box.obj"}));

    // Scene 4 - Sphere in a Plane

    /*glm::vec3 emmiter_1{0.0f, 0.0f, 0.0f};
    glm::vec3 albedo_1 = glm::vec3{1.0f, 0.0f, 0.0f};

    glm::vec3 emmiter_2{0.0f, 0.0f, 0.0f};
    glm::vec3 albedo_2 = glm::vec3{1.0f, 1.0f, 1.0f};

    glm::vec3 emmiter_3{1.0f, 1.0f, 1.0f};
    glm::vec3 albedo_3{0.0f, 0.0f, 0.0f};

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_1, albedo_1)),
                                                                   glm::vec3{0.0f, 0.0f, 0.0f}, 0.5f}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_2, albedo_2)),
                                                                   glm::vec3{0.0f, -100.5f, 0.0f}, 100.0f}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_3, albedo_3)),
                                                                   glm::vec3{0.0f, 15.0f, 0.0f}, 10.25f}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter_3, albedo_3)),
                                                                     glm::vec3{-0.5f, 0.75f, -0.5f},
                                                                     glm::vec3{0.5f, 0.75f, 0.5f},
                                                                     glm::vec3{-0.5f, 0.75f, 0.5f}}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter_3, albedo_3)),
                                                                     glm::vec3{-0.5f, 0.75f, -0.5f},
                                                                     glm::vec3{0.5f, 0.75f, -0.5f},
                                                                     glm::vec3{0.5f, 0.75f, 0.5f}}));*/
}
