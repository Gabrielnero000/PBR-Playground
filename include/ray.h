#ifndef RAY_H
#define RAY_H

/*******************************************************************************
    Class Ray:

  - PBR's core element. An ray is an straight line given by p(t) = O + t*D, 
    where O is the ray's origin, D is the ray's direction and t is a real number.

--------------------------------------------------------------------------------

  Variables:

  - glm::vec3 origin_;
    - Stores the ray's origin.

  - glm::vec3 direction_;
    - Stores the ray's direction.

--------------------------------------------------------------------------------

  Methods:

  - Ray(const glm::vec3 &origin, const glm::vec3 &direction):
    - Constructor.

  - ~Ray():
    - Deconstructor.

  - glm::vec3 evaluate(float t) const:
    - Returns the ray equation's solution.

********************************************************************************/

#include <glm/glm.hpp>

class Ray
{
public:
  Ray(const glm::vec3 &origin, const glm::vec3 &direction);
  ~Ray();
  glm::vec3 evaluate(float t) const;

  glm::vec3 origin_;
  glm::vec3 direction_;
};

#endif