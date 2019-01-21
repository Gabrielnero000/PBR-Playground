#ifndef CAMERA_H
#define CAMERA_H

/*******************************************************************************
    Class Camera:

  - Abstract class for the camera, witch is responsable for the way that the
    the output image looks like (geometrically speaking).

--------------------------------------------------------------------------------

  Variables:

  - glm::vec3 up_:
    - Up direction of the camera (usually (0, 1, 0)).

  - glm::vec3 look_at_:
    - Where the camera is "looking at".

  - glm::vec3 position_:
    - Position of the camera.
    
  - glm::vec3 direction_:
    - Direction that the camera is looking at (look_at - position)

--------------------------------------------------------------------------------

  Methods:

  - Camera(const glm::vec3 &up, const glm::vec3 &look_at, const glm::vec3 &position):
    - Constructor.

  - virtual ~Camera():
    - Deconstructor. 'Virtual' because it's an abstract class.

  - void setPosition(const glm::vec3 &position):
    - Changes the camera position.

  - void setUp(const glm::vec3 &up):
    - Changes the up direction of the camera.

  - void setLookAt(const glm::vec3 &look_at):
    - Changes where the camera is looking at.

  - virtual Ray getRay(const glm::vec2 &coordinates) const = 0:
    - Given an pair of coordinates u, v (both between [0, 1]),
      gets a Ray from the camera to scene in world space. Since
      every camera model has an different ray calculation, must
      be overloaded. 

********************************************************************************/

#include "onb.h"
#include "ray.h"

class Camera
{
  public:
    Camera(
        const glm::vec3 &up,
        const glm::vec3 &look_at,
        const glm::vec3 &position);
    virtual ~Camera();

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