#include "main.h"
#include <fenv.h>

typedef std::vector<Primitive::PrimitivePtr> Scene;

void read(const std::string &filename, Scene &triangles)
{
    std::vector<Vec3f> vertex_temp;
    std::string line;
    std::ifstream mesh;
    mesh.open(filename);
    Vec3f emmiter_zero = Vec3f(0.0f, 0.0f, 0.0f);
    Vec3f albedo_green = Vec3f(0.001f, 0.9f, 0.001f);

    int index[3];

    if (mesh.is_open())
    {
        while (getline(mesh, line))
        {
            switch (line[0])
            {
            case 'v':
            {
                for (size_t i = 0, j = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        index[j] = i;
                        j++;
                    }
                }

                vertex_temp.push_back(Vec3f{
                    std::stof(line.substr(index[0] + 1, index[1] - index[0])),
                    std::stof(line.substr(index[1] + 1, index[2] - index[1])),
                    std::stof(line.substr(index[2] + 1, (line.size() - 1) - index[2]))});
            }
            break;

            case 'f':
            {
                for (size_t i = 0, j = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        index[j] = i;
                        j++;
                    }
                }

                Vec3f v_1 = vertex_temp[std::stoi(line.substr(index[0] + 1, index[1] - index[0])) - 1];
                Vec3f v_2 = vertex_temp[std::stoi(line.substr(index[1] + 1, index[2] - index[1])) - 1];
                Vec3f v_3 = vertex_temp[std::stoi(line.substr(index[2] + 1, (line.size() - 1) - index[2])) - 1];

                triangles.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_green)),
                                                                         "mesh_triangle", v_1, v_2, v_3)));
            }
            break;

            default:
                break;
            }
        }
    }
}

// Scene 1 - Cornell Box
Scene cornellBox()
{
    Scene primitives;

    // No emmiter
    Vec3f emmiter_zero = Vec3f(0.0f, 0.0f, 0.0f);

    // Light emmitter
    Vec3f emmiter_light = Vec3f(40.0f, 40.0f, 40.0f);

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

    // // Red sphere
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_red)),
    //                                                         "sphere_red",
    //                                                         Vec3f(-0.4f, -0.5f, 0.5f),
    //                                                         0.25f)));

    // // Green sphere
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Specular(emmiter_zero, albedo_white, 0.5f)),
    //                                                         "sphere_metal",
    //                                                         Vec3f(0.0f, -0.5f, 0.25f),
    //                                                         0.25f)));

    // // Blue sphere
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_blue)),
    //                                                         "sphere_blue",
    //                                                         Vec3f(0.4f, -0.5f, 0.5f),
    //                                                         0.25f)));

    // Floor
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            "floor",
                                                            Vec3f(0.0f, -100.75f, 0.0f),
                                                            100.0f)));

    // // Right wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         "right_wall",
    //                                                         Vec3f(100.75f, 0.0f, 0.0f),
    //                                                         100.0f)));

    // // Left Wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         "left_wall",
    //                                                         Vec3f(-100.75f, 0.0f, 0.0f),
    //                                                         100.0f)));

    // // Roof
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         Vec3f(0.0f, 100.75f, 0.0f),
    //                                                         100.0f)));

    // // Back wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         Vec3f(0.0f, 0.0f, -100.5f),
    //                                                         100.0f)));

    // Light
    primitives.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter_light, albedo_white)),
                                                              "triangle_1",
                                                              Vec3f(-0.5f, 0.7f, 0.7f),
                                                              Vec3f(0.5f, 0.7f, 0.7f),
                                                              Vec3f(-0.5f, 0.7f, -0.7f))));

    primitives.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter_light, albedo_white)),
                                                              "triangle_2",
                                                              Vec3f(0.5f, 0.7f, 0.7f),
                                                              Vec3f(0.5f, 0.7f, -0.7f),
                                                              Vec3f(-0.5f, 0.7f, -0.7f))));

    read("monkey.obj", primitives);

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
    Vec3f background_color_from = Vec3f(0.0f, 0.0f, 0.0f);
    Vec3f background_color_to = Vec3f(0.0f, 0.0f, 0.0f);

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

    BVH acc(scene);

    PathTracer render = PathTracer(output, camera, acc, scene, background_color_from, background_color_to, samples, depth);

    render.integrate();
    output.save("output");

    return EXIT_SUCCESS;
}