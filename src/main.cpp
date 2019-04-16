#include "main.h"
#include <fenv.h>

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

    Scene scene;
    Render render{output, scene, camera, background_color_from, background_color_to, samples, depth};
    scene.load();

    render.integrate();
    output.save("output");

    return EXIT_SUCCESS;
}