#include "render.h"

Render::Render(Output &output,
               Scene &scene,
               Camera &camera,
               glm::vec3 &background_color_from,
               glm::vec3 &background_color_to) : output_{output},
                                                 scene_{scene},
                                                 camera_{camera},
                                                 background_color_from_{background_color_from},
                                                 background_color_to_{background_color_to} {};

Render::~Render() {}

void Render::integrate()
{
    // TODO
}

void Render::test()
{
    Record record;

    // Measure time
    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t y = 0; y < output_.resolution_.y; y++)
    {
        // Print the render progress
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw(6)
                        << std::setprecision(2)
                        << 100.0 * y / (output_.resolution_.y - 1)
                        << "%";

        std::clog << progress_stream.str();

        // for each pixel
        for (std::size_t x = 0; x < output_.resolution_.x; x++)
        {
            // u, v coordinates to the camera
            float u = float(x) / float(output_.resolution_.x);
            float v = float(y) / float(output_.resolution_.y);

            Ray ray{camera_.getRay(glm::vec2{u, v})};

            // Test camera's ray to each primitive
            if (scene_.intersect(ray, MIN_T, MAX_T, record))
            {
                // Visualize the colision based on t
                output_.buffer_[x][y] = glm::vec3{(float)fabs(record.normal_[0]),
                                                  (float)fabs(record.normal_[1]),
                                                  (float)fabs(record.normal_[2])};
            }
            else
            {
                // Make a degrade effect
                glm::vec3 unit = (glm::normalize(ray.direction_));
                float t = 0.5 * (unit.y + 1.0f);
                output_.buffer_[x][y] = (1.0f - t) * background_color_from_ + t * background_color_to_;
            }
        }
    }

    // Print some usefull information
    std::clog << std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s" << std::endl;
}
