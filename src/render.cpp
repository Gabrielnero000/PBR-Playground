#include "render.h"

Render::Render(Output &output,
               Scene &scene,
               Camera &camera,
               glm::vec3 &background_color_from,
               glm::vec3 &background_color_to,
               const int samples,
               const int ray_depth) : output_{output},
                                      scene_{scene},
                                      camera_{camera},
                                      background_color_from_{background_color_from},
                                      background_color_to_{background_color_to},
                                      samples_{samples},
                                      ray_depth_{ray_depth} {};

Render::~Render() {}

glm::vec3 Render::Color(const Ray &ray, Record &record, int depth)
{
    glm::vec3 L_o{0.0f, 0.0f, 0.0f};

    if (depth < ray_depth_)
    {
        if (scene_.intersect(ray, MIN_T, MAX_T, record))
        {
            ONB onb;
            onb.setFromV(record.normal_);

            glm::vec3 w_in = glm::normalize(ray.direction_);
            glm::vec3 w_out = glm::normalize(scene_.primitives_[record.index_]->material_->directionGenerator() * onb.inverse_);

            Ray next_ray = Ray(record.point_ + (record.normal_ * 0.001f), w_out);

            return scene_.primitives_[record.index_]->material_->emmiter_ +
                   2.0f * (float)M_PI *
                       scene_.primitives_[record.index_]->material_->BRDF(w_in, w_out) *
                       Color(next_ray, record, depth + 1) *
                       (float)fabs(glm::dot(next_ray.direction_, record.normal_));
        }
        else
        {
            glm::vec3 unit = (glm::normalize(ray.direction_));
            float t = 0.5 * (unit.y + 1.0f);
            return (1.0f - t) * background_color_from_ + t * background_color_to_;
        }
    }
    return L_o;
}

void Render::integrate()
{
    const float inv_samples = 1.0f / samples_;

    // Measure time
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int y = 0; y < (int)output_.resolution_.y; y++)
    {
        // Print the render progress
        /*std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw(6)
                        << std::setprecision(2)
                        //<< "Thread ID: " << omp_get_thread_num() << " "
                        << 100.0 * y / (output_.resolution_.y - 1)
                        << "%";

        std::clog << progress_stream.str();*/
        Record record;

        // for each pixel
        for (int x = 0; x < (int)output_.resolution_.x; x++)
        {

            // for each sample
            for (int i = 0; i < samples_; i++)
            {
                // u, v coordinates to the camera
                float u = (float(x) + (float)drand48()) / (float)(output_.resolution_.x);
                float v = (float(y) + (float)drand48()) / (float)(output_.resolution_.y);

                Ray ray{camera_.getRay(glm::vec2{u, v})};

                output_.buffer_[x][y] += Color(ray, record, 0);
            }
            output_.buffer_[x][y] *= inv_samples;
        }
    }
    // Print some usefull information
    //std::clog << std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s" << std::endl;
}
