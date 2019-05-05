#include "Cameras/ortho_camera.h"

OrthoCamera::OrthoCamera(const float min_x,
                         const float max_x,
                         const float min_y,
                         const float max_y,
                         const Vec3f &up,
                         const Vec3f &look_at,
                         const Vec3f &position) : Camera::Camera{up, look_at, position},
                                                  min_x_{min_x},
                                                  max_x_{max_x},
                                                  min_y_{min_y},
                                                  max_y_{max_y} {}

OrthoCamera::~OrthoCamera() {}

Ray OrthoCamera::getRay(const float u, const float v) const
{
    float width = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    // origin.x = x_coord * WIDTH + min_x
    // origin.y = y_coord * HEIGHT + min_y
    // origin.z = 0.0f
    Vec3f origin{u * width + min_x_,
                 v * height + min_y_,
                 0.0f};

    // Ray still in camera's space, must transform it to world space
    return Ray(onb_.applyONB(origin + position_),
               onb_.applyONB(look_at_).as_unit());
}