#include "Cameras/camera.h"

Camera::Camera(const Vec3f &up,
               const Vec3f &look_at,
               const Vec3f &position) : up_{up},
                                        look_at_{look_at},
                                        position_{position},
                                        direction_{(look_at - position).as_unit()}
{
    //Mount the camera basis
    onb_.setFromUW(up_.cross(-direction_).as_unit(), -direction_);
}

Camera::~Camera() {}

void Camera::setPosition(const Vec3f &position)
{
    position_ = position;
    //Must uptade direction and camera basis
    direction_ = (look_at_ - position_).as_unit();
    onb_.setFromUW(up_.cross(-direction_).as_unit(), -direction_);
}

void Camera::setUp(const Vec3f &up)
{
    up_ = up;
    //Must uptade camera basis
    onb_.setFromUW(up_.cross(-direction_).as_unit(), -direction_);
}

void Camera::setLookAt(const Vec3f &look_at)
{
    look_at_ = look_at;
    //Must uptade direction and camera basis
    direction_ = (look_at_ - position_).as_unit();
    onb_.setFromUW(up_.cross(-direction_).as_unit(), -direction_);
}