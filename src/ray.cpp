#include "ray.h"

Ray::Ray(){};

Ray::Ray(const glm::vec3 &origin,
         const glm::vec3 &direction) : origin_{origin},
                                       direction_{direction} {}

Ray::~Ray() {}

glm::vec3 Ray::evaluate(float t) const { return origin_ + t * direction_; }