#ifndef CAMERA_H
#define CAMERA_H

#include "onb.h"
#include "ray.h"

class Camera
{
  public:
    Camera(
        const glm::vec3 &up,
        const glm::vec3 &look_at,
        const glm::vec3 &position);
    ~Camera();

    void setPosition(const glm::vec3 &position);
    void setUp(const glm::vec3 &up);
    void setLookAt(const glm::vec3 &look_at);

    virtual Ray getRay(const glm::vec2 &coordinates) const = 0;

    glm::vec3 up_;
    glm::vec3 look_at_;
    glm::vec3 position_;
    glm::vec3 direction_;

    ONB onb_;
};

#endif