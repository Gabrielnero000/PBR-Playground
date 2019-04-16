#ifndef PINHOLE_CAMERA_H
#define PINHOLE_CAMERA_H

#include "camera.h"

class PinholeCamera : public Camera
{
public:
  PinholeCamera(const float min_x,
                const float max_x,
                const float min_y,
                const float max_y,
                const float focal_distance,
                const Vec3f &up,
                const Vec3f &look_at,
                const Vec3f &position);
  ~PinholeCamera();

  Ray getRay(const float u, const float v) const;

  float min_x_;
  float max_x_;
  float min_y_;
  float max_y_;
  float focal_distance_;
};

#endif