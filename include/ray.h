#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{
public:
  Ray(const glm::vec3 &origin, const glm::vec3 &direction);
  glm::vec3 evaluate(float t) const;

  glm::vec3 origin_;
  glm::vec3 direction_;
};

#endif