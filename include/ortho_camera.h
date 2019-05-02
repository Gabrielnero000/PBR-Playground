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
              const Vec3f &up,
              const Vec3f &look_at,
              const Vec3f &position);
  ~OrthoCamera();

  Ray getRay(const float u, const float v) const;

  float min_x_;
  float max_x_;
  float min_y_;
  float max_y_;
};

#endif