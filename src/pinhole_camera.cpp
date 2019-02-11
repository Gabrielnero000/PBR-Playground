#include "pinhole_camera.h"

PinholeCamera::PinholeCamera(const float min_x,
                             const float max_x,
                             const float min_y,
                             const float max_y,
                             const float focal_distance,
                             const glm::vec3 &up,
                             const glm::vec3 &look_at,
                             const glm::vec3 &position) : Camera::Camera{up, look_at, position},
                                                          min_x_{min_x},
                                                          max_x_{max_x},
                                                          min_y_{min_y},
                                                          max_y_{max_y},
                                                          focal_distance_{focal_distance} {}

PinholeCamera::~PinholeCamera() {}

Ray PinholeCamera::getRay(const glm::vec2 &coordinates) const
{
    float width = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    glm::vec3 direction{coordinates.x * width + min_x_,
                        coordinates.y * height + min_y_,
                        -focal_distance_};

    // Ray still in camera's space, must transform it to world space
    return Ray{onb_.basis_ * position_,
               glm::normalize(onb_.basis_ * direction)};
}