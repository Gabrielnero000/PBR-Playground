#include "Utils/ray.h"

Ray::Ray(){};

Ray::Ray(const Vec3f &origin,
         const Vec3f &direction) : origin_{origin},
                                       direction_{direction} {}

Ray::~Ray() {}

Vec3f Ray::evaluate(const float t) const { return origin_ + t * direction_; }