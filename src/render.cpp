#include "render.h"

Render::Render(Output &output,
               Scene &scene,
               Camera &camera,
               glm::vec3 &background_color_from,
               glm::vec3 &background_color_to,
               const int samples) : output_{output},
                                    scene_{scene},
                                    camera_{camera},
                                    background_color_from_{background_color_from},
                                    background_color_to_{background_color_to},
                                    samples_{samples} {};

Render::~Render() {}

void Render::integrate()
{
    Record record;
    const float samples = 1.0f / samples_;

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

            // for each sample
            for (int i = 0; i < samples_; i++)
            {
                // u, v coordinates to the camera
                float u = (float(x) + (float)drand48()) / (float)(output_.resolution_.x);
                float v = (float(y) + (float)drand48()) / (float)(output_.resolution_.y);

                Ray ray{camera_.getRay(glm::vec2{u, v})};

                // Test camera's ray to each primitive
                if (scene_.intersect(ray, MIN_T, MAX_T, record))
                {
                    // Visualize the colision based on t
                    output_.buffer_[x][y] = glm::vec3{fabs(record.normal_.x), fabs(record.normal_.y), fabs(record.normal_.z)};
                }
                else
                {
                    // Make a gradient effect
                    glm::vec3 unit = (glm::normalize(ray.direction_));
                    float t = 0.5 * (unit.y + 1.0f);
                    output_.buffer_[x][y] = (1.0f - t) * background_color_from_ + t * background_color_to_;
                }
            }
            output_.buffer_[x][y] *= samples;
        }
    }

    // Print some usefull information
    std::clog << std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s" << std::endl;
}
