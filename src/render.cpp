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
    for (int y = 0; y < output_.resolution_.y; y++)
    {
        for (int x = 0; x < output_.resolution_.x; x++)
        {
            float u = float(x) / float(output_.resolution_.x);
            float v = float(y) / float(output_.resolution_.y);

            Ray ray{camera_.getRay(glm::vec2{u, v})};

            if (scene_.intersect(ray, 0.0f, 10.0f, record))
            {
                output_.buffer_[x][y] = glm::vec3{record.t_ * 0.2f};
            }
            else
            {
                glm::vec3 unit = (glm::normalize(ray.direction_));
                float t = 0.5 * (unit.y + 1.0f);
                output_.buffer_[x][y] = (1.0f - t) * background_color_from_ + t * background_color_to_;
            }
        }
    }
}
