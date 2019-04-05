#include "main.h"
#include <fenv.h>

int main()
{

    // feenableexcept(FE_INVALID);
    // Output params
    glm::vec2 resolution = {512, 512};

    //Render params
    //glm::vec3 background_color_from = {1.0f, 1.0f, 1.0f}; // White
    //glm::vec3 background_color_to = {0.5f, 0.7f, 1.0f};   // Ciano
    glm::vec3 background_color_from = {0.0f, 0.0f, 0.0f};
    glm::vec3 background_color_to = {0.0f, 0.0f, 0.0f};

    int samples = 16000;
    int depth = 5;

    //Camera params - 1:1 presset
    float min_x = -1.0f;
    float max_x = 1.0f;
    float min_y = -1.0f;
    float max_y = 1.0f;
    float focal_distance = 2.0f;

    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    glm::vec3 look_at = {0.0f, 0.0f, -1.0f};
    glm::vec3 position = {0.0f, 0.0f, 2.5f};

    //-----------------------------------------------------------------------------------

    Output output{resolution};

    PinholeCamera camera{min_x, max_x, min_y, max_y, focal_distance,
                         up, look_at, position};

    Scene scene;
    Render render{output, scene, camera, background_color_from, background_color_to, samples, depth};
    scene.load();

    render.integrate();
    output.save("output");

    return EXIT_SUCCESS;
}