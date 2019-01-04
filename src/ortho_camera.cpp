#include "ortho_camera.h"

OrthoCamera::OrthoCamera(const float min_x,
                         const float max_x,
                         const float min_y,
                         const float max_y,
                         const glm::vec3 &up,
                         const glm::vec3 &look_at,
                         const glm::vec3 &position) : Camera::Camera{up, look_at, position},
                                                      min_x_{min_x},
                                                      max_x_{max_x},
                                                      min_y_{min_y},
                                                      max_y_{max_y} {}

OrthoCamera::~OrthoCamera() {}

Ray OrthoCamera::getRay(const glm::vec2 &coordinates) const
{
    float width = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    glm::vec3 origin{coordinates.x * width + min_x_,
                     coordinates.y * height + min_y_,
                     0.0f};

    return Ray{onb_.basis_ * origin + position_,
               glm::normalize(onb_.basis_ * glm::vec3{0.0f, 0.0f, -1.0f})};
}