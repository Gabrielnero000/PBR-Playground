#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H

#include "camera.h"

class OrthoCamera : public Camera
{
public:
  OrthoCamera(const float min_x,
              const float max_x,
              const float min_y,
              const float max_y,
              const glm::vec3 &up,
              const glm::vec3 &look_at,
              const glm::vec3 &position);
  ~OrthoCamera();

  Ray getRay(const glm::vec2 &coordinates) const;

  float min_x_;
  float max_x_;
  float min_y_;
  float max_y_;
};

#endif