#include "main.h"
#include <fenv.h>

typedef std::vector<Primitive::PrimitivePtr> Scene;

// Scene 1 - Cornell Box
// Scene cornellBox()
// {
//     Scene primitives;

//     // No emmiter
//     Vec3f emmiter_zero = Vec3f(0.0f, 0.0f, 0.0f);

//     // Light emmitter
//     Vec3f emmiter_light = Vec3f(2.0f, 2.0f, 2.0f);

//     // Red albedo
//     Vec3f albedo_red = Vec3f(0.75f, 0.25f, 0.25f);

//     // Green albedo
//     //Vec3f albedo_green = Vec3f(0.25f, 0.75f, 0.25f);

//     // Blue albedo
//     Vec3f albedo_blue = Vec3f(0.25f, 0.25f, 0.75f);

//     // White albedo
//     Vec3f albedo_white = Vec3f(0.999f, 0.999f, 0.999f);

//     // Gray albedo
//     Vec3f albedo_gray = Vec3f(0.999f, 0.999f, 0.999f);

//     //Left sphere
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Specular(
//             Texture::TexturePtr(new Color(albedo_white)),
//             0.0f)),
//         "Left_sphere",
//         Vec3f(-0.75f, -0.999f, -0.1f),
//         0.5f)));

//     // Center sphere

//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Emmiter(
//             Texture::TexturePtr(new Color(emmiter_light)))),
//         "Center_sphere",
//         Vec3f(0.0f, 2.0f, 0.0f),
//         0.5f)));

//     // Right sphere
//     // primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//     //     Material::MaterialPtr(new Dieletric(
//     //         Texture::TexturePtr(new Color(albedo_white)),
//     //         1.45f)),
//     //     "Right_sphere",
//     //     Vec3f(0.75f, -0.999f, 0.3f),
//     //     0.5f)));

//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Mix(
//             Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Color(albedo_white)))),
//             Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(albedo_white)), 0.0f)),
//             0.05f)),
//         "Right_sphere",
//         Vec3f(0.75f, -0.999f, 0.3f),
//         0.5f)));

//     // Floor
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Diffuse(
//             Texture::TexturePtr(new Perlin(1.0f)))),
//         "floor",
//         Vec3f(0.0f, -101.5f, 0.0f),
//         100.0f)));

//     // Right wall
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Diffuse(
//             Texture::TexturePtr(new Color(albedo_blue)))),
//         "right_wall",
//         Vec3f(101.75f, 0.0f, 0.0f),
//         100.0f)));

//     // Left Wall
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Diffuse(
//             Texture::TexturePtr(new Color(albedo_red)))),
//         "left_wall",
//         Vec3f(-101.75f, 0.0f, 0.0f),
//         100.0f)));

//     // Roof
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Diffuse(
//             Texture::TexturePtr(new Color(albedo_white)))),
//         "roof",
//         Vec3f(0.0f, 101.75f, 0.0f),
//         100.0f)));

//     // Back wall
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Diffuse(
//             Texture::TexturePtr(new Color(albedo_white)))),
//         "back_wall",
//         Vec3f(0.0f, 0.0f, -102.5f),
//         100.0f)));

//     // Front wall
//     primitives.push_back(Primitive::PrimitivePtr(new Sphere(
//         Material::MaterialPtr(new Diffuse(
//             Texture::TexturePtr(new Color(albedo_white)))),
//         "back_wall",
//         Vec3f(0.0f, 0.0f, 102.5f),
//         100.0f)));

//     // int nx, ny, nn;
//     // unsigned char *tex_data = stbi_load("earth.jpg", &nx, &ny, &nn, 0);

//     // Material *world = new Diffuse(Texture::TexturePtr(new Image(tex_data, nx, ny)));

//     // read("world.obj", primitives, world);

//     return primitives;
// }

Scene makeScene()
{
    Scene primitives;

    Vec3f walls_albedo(0.8f);
    Vec3f light_emmiter(1.0f);

    int background_x, background_y, background_n;
    unsigned char *background_img = stbi_load("scene/background.png", &background_x, &background_y, &background_n, 0);

    int floor_x, floor_y, floor_n;
    unsigned char *floor_img = stbi_load("scene/floor.jpg", &floor_x, &floor_y, &floor_n, 0);

    int chair_x, chair_y, chair_n;
    unsigned char *chair_img = stbi_load("scene/chair.png", &chair_x, &chair_y, &chair_n, 0);

    int carpet_x, carpet_y, carpet_n;
    unsigned char *carpet_img = stbi_load("scene/carpet.jpg", &carpet_x, &carpet_y, &carpet_n, 0);

    int picture_x, picture_y, picture_n;
    unsigned char *picture_img = stbi_load("scene/picture.jpg", &picture_x, &picture_y, &picture_n, 0);

    int curtain_x, curtain_y, curtain_n;
    unsigned char *curtain_img = stbi_load("scene/curtain.jpg", &curtain_x, &curtain_y, &curtain_n, 0);

    Material *background_ = new Emmiter(Texture::TexturePtr(new Image(background_img, background_x, background_y)), 3.0f);

    Material *carpet_ = new Diffuse(Texture::TexturePtr(new Image(carpet_img, carpet_x, carpet_y)));

    Material *walls_ = new Diffuse(Texture::TexturePtr(new Color(walls_albedo)));

    Material *picture_ = new Mix(
        Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Image(picture_img, picture_x, picture_y)))),
        Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.05f)),
        0.01f);

    Material *table_ = new Mix(
        Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Color(Vec3f(0.0f))))),
        Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.0f)),
        0.1f);

    Material *table_marm_ = new Mix(
        Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Perlin(3.0f)))),
        Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.0f)),
        0.075f);

    Material *curtains_ = new Diffuse(Texture::TexturePtr(new Image(curtain_img, curtain_x, curtain_y)));

    Material *curtain_pipe_ = new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.0f);

    Material *radiator_ = new Specular(Texture::TexturePtr(new Color(Vec3f(0.831f, 0.686f, 0.216f))), 0.05f);

    Material *floor_ = new Mix(
        Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Image(floor_img, floor_x, floor_y)))),
        Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.15f)),
        0.1f);

    Material *chairs_ = new Mix(
        Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Image(chair_img, chair_x, chair_y)))),
        Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.2f)),
        0.05f);

    Material *window_1_ = new Dieletric(Texture::TexturePtr(new Color(Vec3f(0.5f))), 1.45f);
    Material *window_2_ = new Dieletric(Texture::TexturePtr(new Color(Vec3f(0.6f))), 1.45f);

    primitives.push_back(Primitive::PrimitivePtr(new Sphere(
        Material::MaterialPtr(new Emmiter(
            Texture::TexturePtr(new Color(light_emmiter)),
            3.0f)),
        "light",
        Vec3f(0.0f, 5.25f, -1.25f),
        1.0f)));

    primitives.push_back(Primitive::PrimitivePtr(new Sphere(
        Material::MaterialPtr(new Mix(
            Material::MaterialPtr(new Diffuse(Texture::TexturePtr(new Color(Vec3f(1.0f))))),
            Material::MaterialPtr(new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.0f)),
            0.1f)),
        "sphere_1",
        Vec3f(-0.6f, 0.7f, 0.7f),
        0.2f)));

    primitives.push_back(Primitive::PrimitivePtr(new Sphere(
        Material::MaterialPtr(
            new Dieletric(Texture::TexturePtr(new Color(Vec3f(1.0f))), 1.5f)),
        "sphere_2",
        Vec3f(-0.1f, 0.7f, 0.7f),
        0.2f)));

    primitives.push_back(Primitive::PrimitivePtr(new Sphere(
        Material::MaterialPtr(
            new Specular(Texture::TexturePtr(new Color(Vec3f(1.0f))), 0.0f)),
        "sphere_3",
        Vec3f(0.4f, 0.7f, 0.7f),
        0.2f)));

    read("scene/chair_left.obj", primitives, chairs_);
    read("scene/chair_right.obj", primitives, chairs_);

    read("scene/table.obj", primitives, table_);
    read("scene/table_marm.obj", primitives, table_marm_);

    read("scene/curtain_left.obj", primitives, curtains_);
    read("scene/curtain_right.obj", primitives, curtains_);

    read("scene/background.obj", primitives, background_);

    read("scene/back_wall.obj", primitives, walls_);
    read("scene/front_wall.obj", primitives, walls_);
    read("scene/left_wall.obj", primitives, walls_);
    read("scene/right_wall.obj", primitives, walls_);
    read("scene/roof.obj", primitives, walls_);

    read("scene/floor.obj", primitives, floor_);

    read("scene/carpet.obj", primitives, carpet_);
    read("scene/curtain_pipe.obj", primitives, curtain_pipe_);

    read("scene/mold.obj", primitives, walls_);

    read("scene/picture.obj", primitives, picture_);

    read("scene/pilar_1.obj", primitives, walls_);
    read("scene/pilar_2.obj", primitives, walls_);

    read("scene/window_1.obj", primitives, window_1_);
    read("scene/window_2.obj", primitives, window_2_);

    read("scene/window_mold.obj", primitives, walls_);

    read("scene/radiator.obj", primitives, radiator_);

    return primitives;
}

int main()
{
    //feenableexcept(FE_INVALID | FE_DIVBYZERO);
    // Output params
    int width = 1280;
    int height = 720;

    //Render params
    //Vec3f background_color_from(1.0f, 1.0f, 1.0f); // White
    //Vec3f background_color_to(0.5f, 0.7f, 1.0f);   // Ciano
    Vec3f background_color_from = Vec3f(0.0f, 0.0f, 0.0f);
    Vec3f background_color_to = Vec3f(0.0f, 0.0f, 0.0f);

    int samples = 10000;
    int depth = 7;

    //Camera params - 1:1 presset
    float min_x = -2.0f;
    float max_x = 2.0f;
    float min_y = -1.125f;
    float max_y = 1.125f;
    float focal_distance = 2.0f;

    Vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    Vec3f look_at = Vec3f(0.0f, 2.5f, -1.0f).as_unit();
    Vec3f position = Vec3f(-0.25f, 1.5f, 4.75f);

    //-----------------------------------------------------------------------------------

    PinholeCamera camera(min_x, max_x, min_y, max_y, focal_distance,
                         up, look_at, position);

    Scene scene = makeScene();

    BVH acc(scene);

    PathTracer render(width, height, camera, acc, scene, background_color_from, background_color_to, samples, depth);

    render.integrate();

    saveToFile("output", render.buffer_);

    return EXIT_SUCCESS;
}