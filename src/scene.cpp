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

    // No emmiter
    glm::vec3 emmiter_zero{0.0f, 0.0f, 0.0f};

    // Light emmitter
    glm::vec3 emmiter_light{2.0f, 2.0f, 2.0f};

    // Red albedo
    glm::vec3 albedo_red{0.9f, 0.001f, 0.0f};

    // Green albedo
    glm::vec3 albedo_green{0.001f, 0.9f, 0.001f};

    // Blue albedo
    glm::vec3 albedo_blue{0.001f, 0.001f, 0.9f};

    // White albedo
    glm::vec3 albedo_white{0.9f, 0.9f, 0.9f};

    // Gray albedo
    glm::vec3 albedo_gray{0.5f, 0.5f, 0.5f};

    // Red sphere
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_red)),
                                                                   glm::vec3{-0.4f, -0.5f, 0.25f}, 0.25f}));

    // Green sphere
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_green)),
                                                                   glm::vec3{0.0f, -0.5f, 0.5f}, 0.25f}));

    // Blue sphere
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_blue)),
                                                                   glm::vec3{0.4f, -0.5f, 0.25f}, 0.25f}));

    // Floor
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                                   glm::vec3{0.0f, -100.75f, 0.0f}, 100.0f}));

    // Right wall
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                                   glm::vec3{100.75f, 0.0f, 0.0f}, 100.0f}));

    // Left Wall
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                                   glm::vec3{-100.75f, 0.0f, 0.0f}, 100.0f}));

    // Roof
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                                   glm::vec3{0.0f, 100.75f, 0.0f}, 100.0f}));

    // Back wall
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{Primitive::MaterialUniquePtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                                   glm::vec3{0.0f, 0.0f, -100.5f}, 100.0f}));
                                                                   
    // Light
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter_light, albedo_white)),
                                                                     glm::vec3{-0.5f, 0.7f, 0.7f},
                                                                     glm::vec3{0.5f, 0.7f, 0.7f},
                                                                     glm::vec3{-0.5f, 0.7f, -0.7f}}));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{Primitive::MaterialUniquePtr(new Lambertian(emmiter_light, albedo_white)),
                                                                     glm::vec3{0.5f, 0.7f, 0.7f},
                                                                     glm::vec3{0.5f, 0.7f, -0.7f},
                                                                     glm::vec3{-0.5f, 0.7f, -0.7f}}));
}
