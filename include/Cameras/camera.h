#ifndef CAMERA_H
#define CAMERA_H

#include "Utils/onb.h"
#include "Utils/ray.h"

class Camera
{
public:
  Camera(
      const Vec3f &up,
      const Vec3f &look_at,
      const Vec3f &position);
  virtual ~Camera();

  void setPosition(const Vec3f &position);
  void setUp(const Vec3f &up);
  void setLookAt(const Vec3f &look_at);

  virtual Ray getRay(const float u, const float v) const = 0;

  Vec3f up_;
  Vec3f look_at_;
  Vec3f position_;
  Vec3f direction_;

  ONB onb_;
};

#endif