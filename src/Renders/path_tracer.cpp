#include "Renders/path_tracer.h"

PathTracer::PathTracer(const int widht,
                       const int height,
                       Camera &camera,
                       Accelerator &accelerator,
                       std::vector<Primitive::PrimitivePtr> &primitives,
                       Vec3f &background_color_from,
                       Vec3f &background_color_to,
                       const int samples,
                       const int ray_depth) : Render::Render(widht, height, camera, accelerator, primitives),
                                              background_color_from_{background_color_from},
                                              background_color_to_{background_color_to},
                                              samples_{samples},
                                              ray_depth_{ray_depth} {};

PathTracer::~PathTracer() {}

Vec3f PathTracer::Color(const Ray &ray, Record &record, int depth)
{
    if (accelerator_.trace(ray, MIN_T, MAX_T, record))
    {
        Ray w_out;
        Vec3f attenuation;

        if (depth < ray_depth_ && primitives_[record.index_]->material_->scatter(ray, record, attenuation, w_out))
            return primitives_[record.index_]->material_->emmiter(record.u_, record.v_, record.point_) +
                   attenuation * Color(w_out, record, ++depth); // w_out.direction_.dot(record.normal_);
        else
            return primitives_[record.index_]->material_->emmiter(record.u_, record.v_, record.point_);
    }
    Vec3f unit = ray.direction_.as_unit();
    float t = 0.5 * (unit[1] + 1.0f);
    return (1.0f - t) * background_color_from_ + t * background_color_to_;
}

void PathTracer::integrate()
{
    const float inv_samples = 1.0f / samples_;

    // Measure time
    auto start = std::chrono::steady_clock().now();
    int progress = 0;
#pragma omp parallel for schedule(dynamic, 1)
    for (int y = 0; y < height_; y++)
    {
        std::minstd_rand gen(std::random_device{}());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        // Print the render progress
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw(6)
                        << std::setprecision(2)
                        << 100.0 * progress / (height_ - 1)
                        << "%";

        std::clog << progress_stream.str();

        Record record;

        // for each pixel
        for (int x = 0; x < width_; x++)
        {
            // for each sample
            for (int i = 0; i < samples_; i++)
            {
                // u, v coordinates to the camera
                float u = (float(x) + (float)dist(gen)) / (float)(width_);
                float v = (float(y) + (float)dist(gen)) / (float)(height_);

                Ray ray = camera_.getRay(u, v);

                buffer_[x][y] += Color(ray, record, 0);
            }
            buffer_[x][y] *= inv_samples;
        }
#pragma omp atomic
        progress++;
    }
    // Print some usefull information
    std::clog << std::endl;
    auto finish = std::chrono::steady_clock().now();
    std::chrono::duration<float> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s" << std::endl;
}