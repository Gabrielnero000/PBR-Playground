#include "pinhole_camera.h"

PinholeCamera::PinholeCamera(const float min_x,
                             const float max_x,
                             const float min_y,
                             const float max_y,
                             const float focal_distance,
                             const Vec3f &up,
                             const Vec3f &look_at,
                             const Vec3f &position) : Camera::Camera{up, look_at, position},
                                                      min_x_{min_x},
                                                      max_x_{max_x},
                                                      min_y_{min_y},
                                                      max_y_{max_y},
                                                      focal_distance_{focal_distance} {}

PinholeCamera::~PinholeCamera() {}

Ray PinholeCamera::getRay(const float u, const float v) const
{
    float width = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    Vec3f direction{u * width + min_x_,
                    v * height + min_y_,
                    -focal_distance_};

    // Ray still in camera's space, must transform it to world space
    return Ray(onb_.applyONB(position_),
               onb_.applyONB(direction).as_unit());
}