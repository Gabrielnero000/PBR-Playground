#include "main.h"
#include <fenv.h>

typedef std::vector<Primitive::PrimitivePtr> Scene;

// void read(const std::string &filename, Scene &triangles)
// {
//     std::vector<Vec3f> vertex_temp;
//     std::string line;
//     std::ifstream mesh;
//     mesh.open(filename);
//     Vec3f emmiter(0.0f, 0.0f, 0.0f);
//     Vec3f albedo(0.01f, 0.9f, 0.01f);

//     int index[3];

//     if (mesh.is_open())
//     {
//         while (getline(mesh, line))
//         {
//             switch (line[0])
//             {
//             case 'v':
//             {
//                 for (size_t i = 0, j = 0; i < line.size(); i++)
//                 {
//                     if (line[i] == ' ')
//                     {
//                         index[j] = i;
//                         j++;
//                     }
//                 }

//                 vertex_temp.push_back(Vec3f{
//                     std::stof(line.substr(index[0] + 1, index[1] - index[0])),
//                     std::stof(line.substr(index[1] + 1, index[2] - index[1])),
//                     std::stof(line.substr(index[2] + 1, (line.size() - 1) - index[2]))});
//             }
//             break;

//             case 'f':
//             {
//                 for (size_t i = 0, j = 0; i < line.size(); i++)
//                 {
//                     if (line[i] == ' ')
//                     {
//                         index[j] = i;
//                         j++;
//                     }
//                 }

//                 Vec3f v_1 = vertex_temp[std::stoi(line.substr(index[0] + 1, index[1] - index[0])) - 1];
//                 Vec3f v_2 = vertex_temp[std::stoi(line.substr(index[1] + 1, index[2] - index[1])) - 1];
//                 Vec3f v_3 = vertex_temp[std::stoi(line.substr(index[2] + 1, (line.size() - 1) - index[2])) - 1];

//                 triangles.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter, albedo)),
//                                                                          "mesh_triangle", v_1, v_2, v_3, false)));
//             }
//             break;

//             default:
//                 break;
//             }
//         }
//     }
// }

void read(const std::string &filename, Scene &triangles)
{
    objl::Loader loader;

    Vec3f emmiter(0.0f, 0.0f, 0.0f);
    Vec3f albedo(0.01f, 0.9f, 0.01f);
    bool loadout = loader.LoadFile(filename);

    if (loadout)
    {
        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = loader.LoadedMeshes[i];
            for (int j = 0; j < curMesh.Vertices.size(); j += 3)
            {
                Vec3f v_1(curMesh.Vertices[j].Position.X,
                          curMesh.Vertices[j].Position.Y,
                          curMesh.Vertices[j].Position.Z);

                Vec3f v_2(curMesh.Vertices[j + 1].Position.X,
                          curMesh.Vertices[j + 1].Position.Y,
                          curMesh.Vertices[j + 1].Position.Z);

                Vec3f v_3(curMesh.Vertices[j + 2].Position.X,
                          curMesh.Vertices[j + 2].Position.Y,
                          curMesh.Vertices[j + 2].Position.Z);

                Vec3f n_1(curMesh.Vertices[j].Normal.X,
                          curMesh.Vertices[j].Normal.Y,
                          curMesh.Vertices[j].Normal.Z);

                Vec3f n_2(curMesh.Vertices[j + 1].Normal.X,
                          curMesh.Vertices[j + 1].Normal.Y,
                          curMesh.Vertices[j + 1].Normal.Z);

                Vec3f n_3(curMesh.Vertices[j + 2].Normal.X,
                          curMesh.Vertices[j + 2].Normal.Y,
                          curMesh.Vertices[j + 2].Normal.Z);

                triangles.push_back(Primitive::PrimitivePtr(new Triangle(Material::MaterialPtr(new Lambertian(emmiter, albedo)),
                                                                         "mesh_triangle",
                                                                         v_1, v_2, v_3,
                                                                         n_1, n_2, n_3,
                                                                         false)));
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
    Vec3f emmiter_light = Vec3f(3.0f, 3.0f, 3.0f);

    // Red albedo
    Vec3f albedo_red = Vec3f(0.75f, 0.25f, 0.25f);

    // Green albedo
    //Vec3f albedo_green = Vec3f(0.25f, 0.75f, 0.25f);

    // Blue albedo
    Vec3f albedo_blue = Vec3f(0.25f, 0.25f, 0.75f);

    // White albedo
    Vec3f albedo_white = Vec3f(0.999f, 0.999f, 0.999f);

    // Gray albedo
    Vec3f albedo_gray = Vec3f(0.75f, 0.75f, 0.75f);

    // // Left sphere
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Specular(emmiter_zero, albedo_white, 0.0f)),
    //                                                         "Left_sphere",
    //                                                         Vec3f(-0.75f, -0.999f, -0.1f),
    //                                                         0.5f)));

    // // Center sphere
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Emmiter(emmiter_light, emmiter_zero)),
    //                                                         "Center_sphere",
    //                                                         Vec3f(0.0f, 1.8f, 0.0f),
    //                                                         0.5f)));
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Dieletric(emmiter_zero, albedo_white, 1.6f)),
    //                                                         "Center_sphere",
    //                                                         Vec3f(0.0f, -0.25f, 0.7f),
    //                                                         -0.475f)));

    // // Right sphere
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Dieletric(emmiter_zero, albedo_white, 1.5f)),
    //                                                         "Right_sphere",
    //                                                         Vec3f(0.75f, -0.999f, 0.3f),
    //                                                         0.5f)));

    // Floor
    primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
                                                            "floor",
                                                            Vec3f(0.0f, -101.5f, 0.0f),
                                                            100.0f)));

    // // Right wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_blue)),
    //                                                         "right_wall",
    //                                                         Vec3f(101.75f, 0.0f, 0.0f),
    //                                                         100.0f)));

    // // Left Wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_red)),
    //                                                         "left_wall",
    //                                                         Vec3f(-101.75f, 0.0f, 0.0f),
    //                                                         100.0f)));

    // // Roof
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         "roof",
    //                                                         Vec3f(0.0f, 101.75f, 0.0f),
    //                                                         100.0f)));

    // // Back wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         "back_wall",
    //                                                         Vec3f(0.0f, 0.0f, -102.5f),
    //                                                         100.0f)));
    // // Front wall
    // primitives.push_back(Primitive::PrimitivePtr(new Sphere(Material::MaterialPtr(new Lambertian(emmiter_zero, albedo_gray)),
    //                                                         "back_wall",
    //                                                         Vec3f(0.0f, 0.0f, 102.5f),
    //                                                         100.0f)));

    read("sphere.obj", primitives);

    return primitives;
}

int main()
{
    //feenableexcept(FE_INVALID | FE_DIVBYZERO);
    // Output params
    int width = 512;
    int height = 512;

    //Render params
    Vec3f background_color_from(1.0f, 1.0f, 1.0f); // White
    Vec3f background_color_to(0.5f, 0.7f, 1.0f);   // Ciano
    //Vec3f background_color_from = Vec3f(0.0f, 0.0f, 0.0f);
    //Vec3f background_color_to = Vec3f(0.0f, 0.0f, 0.0f);

    int samples = 100;
    int depth = 5;

    //Camera params - 1:1 presset
    float min_x = -1.0f;
    float max_x = 1.0f;
    float min_y = -1.0f;
    float max_y = 1.0f;
    float focal_distance = 1.0f;

    Vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    Vec3f look_at = Vec3f(0.0f, 0.0f, -1.0f);
    Vec3f position = Vec3f(0.0f, 0.0f, 2.5f);

    //-----------------------------------------------------------------------------------

    PinholeCamera camera(min_x, max_x, min_y, max_y, focal_distance,
                         up, look_at, position);

    Scene scene = cornellBox();

    BVH acc(scene);

    PathTracer render(width, height, camera, acc, scene, background_color_from, background_color_to, samples, depth);

    render.integrate();

    saveToFile("output", render.buffer_);

    return EXIT_SUCCESS;
}