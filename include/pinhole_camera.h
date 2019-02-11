#ifndef PINHOLE_CAMERA_H
#define PINHOLE_CAMERA_H

/*******************************************************************************
    Class OrthoCamera:

  - Class that inherits the class Camera, witch abstracts an Orthographic Camera.
    This camera it's made of an projection plane in the camera's position. The
    rays from that model have always the same direction (camera's look at) and
    the origin is a point in that plane, witch is determined by the u, v
    coordinates.

--------------------------------------------------------------------------------

  Variables:

  - float min_x_:
    - Left projection plane's limit. Affects the proportion of the output image.

  - float max_x_:
    - Right projection plane's limit. Affects the proportion of the output image.

  - float min_y_:
    - Lower projection plane's limit. Affects the proportion of the output image.

  - float max_y_:
    - Upper projection plane's limit. Affects the proportion of the output image.

--------------------------------------------------------------------------------

  Methods:

  - OrthoCamera(const float min_x, const float max_x, const float min_y, const float max_y, 
           const glm::vec3 &up, const glm::vec3 &look_at, const glm::vec3 &position):
    - Constructor.

  - ~OrthoCamera():
    - Deconstructor.

  - Ray getRay(const glm::vec2 &coordinates) const:
    - Returns a Ray in the world space. 

********************************************************************************/

#include "camera.h"

class PinholeCamera : public Camera
{
public:
  PinholeCamera(const float min_x,
              const float max_x,
              const float min_y,
              const float max_y,
              const float focal_distance,
              const glm::vec3 &up,
              const glm::vec3 &look_at,
              const glm::vec3 &position);
  ~PinholeCamera();

  Ray getRay(const glm::vec2 &coordinates) const;

  float min_x_;
  float max_x_;
  float min_y_;
  float max_y_;
  float focal_distance_;
};

#endif