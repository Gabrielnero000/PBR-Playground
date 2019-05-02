#include "main.h"
#include <fenv.h>

typedef std::vector<Primitive::PrimitivePtr> Scene;

// Scene 1 - Cornell Box
Scene cornellBox()
{
    Scene primitives;

    // No emmiter
    Vec3f emmiter_zero = Vec3f(0.0f, 0.0f, 0.0f);

    // Light emmitter
    Vec3f emmiter_light = Vec3f(4.0f, 4.0f, 4.0f);

    // Red albedo
    Vec3f albedo_red = Vec3f(0.9f, 0.001f, 0.0f);

    // Green albedo
    Vec3f albedo_green = Vec3f(0.001f, 0.9f, 0.001f);

    // Blue albedo
    Vec3f albedo_blue = Vec3f(0.001f, 0.001f, 0.9f);

    // White albedo
    Vec3f albedo_white = Vec3f(0.9f, 0.9f, 0.9f);

    // Gray albedo
    Vec3f albedo_gray = Vec3f(0.5f, 0.5f, 0.5f);

    // Red sphere
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_red)),
                                                            Vec3f(-0.4f, -0.5f, 0.5f),
                                                            0.25f)));

    // Green sphere
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Specular(emmiter_zero, albedo_white, 0.5f)),
                                                            Vec3f(0.0f, -0.5f, 0.25f),
                                                            0.25f)));

    // Blue sphere
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_blue)),
                                                            Vec3f(0.4f, -0.5f, 0.5f),
                                                            0.25f)));

    // Floor
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            Vec3f(0.0f, -100.75f, 0.0f),
                                                            100.0f)));

    // Right wall
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            Vec3f(100.75f, 0.0f, 0.0f),
                                                            100.0f)));

    // Left Wall
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            Vec3f(-100.75f, 0.0f, 0.0f),
                                                            100.0f)));

    // Roof
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            Vec3f(0.0f, 100.75f, 0.0f),
                                                            100.0f)));

    // Back wall
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            Vec3f(0.0f, 0.0f, -100.5f),
                                                            100.0f)));

    // Light
    primitives.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter_light, albedo_white)),
                                                              Vec3f(-0.5f, 0.7f, 0.7f),
                                                              Vec3f(0.5f, 0.7f, 0.7f),
                                                              Vec3f(-0.5f, 0.7f, -0.7f))));

    primitives.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter_light, albedo_white)),
                                                              Vec3f(0.5f, 0.7f, 0.7f),
                                                              Vec3f(0.5f, 0.7f, -0.7f),
                                                              Vec3f(-0.5f, 0.7f, -0.7f))));

    return primitives;
}

int main()
{
    // feenableexcept(FE_INVALID);
    // Output params
    int width = 512;
    int height = 512;

    //Render params
    //Vec3f background_color_from = {1.0f, 1.0f, 1.0f}; // White
    //Vec3f background_color_to = {0.5f, 0.7f, 1.0f};   // Ciano
    Vec3f background_color_from = Vec3f(1.0f, 1.0f, 1.0f);
    Vec3f background_color_to = Vec3f(1.0f, 1.0f, 1.0f);

    int samples = 100;
    int depth = 5;

    //Camera params - 1:1 presset
    float min_x = -1.0f;
    float max_x = 1.0f;
    float min_y = -1.0f;
    float max_y = 1.0f;
    float focal_distance = 2.0f;

    Vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    Vec3f look_at = Vec3f(0.0f, 0.0f, -1.0f);
    Vec3f position = Vec3f(0.0f, 0.0f, 2.5f);

    //-----------------------------------------------------------------------------------

    Output output = Output(width, height);

    PinholeCamera camera{min_x, max_x, min_y, max_y, focal_distance,
                         up, look_at, position};

    Scene scene = cornellBox();

    BVH acc = BVH(scene);

    PathTracer render = PathTracer(output, camera, acc, scene, background_color_from, background_color_to, samples, depth);

    render.integrate();
    output.save("output");

    return EXIT_SUCCESS;
}