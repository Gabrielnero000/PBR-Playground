#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec.h"

class Ray
{
  public:
	Ray();
	Ray(const Vec3f &origin, const Vec3f &direction);
	~Ray();
	Vec3f evaluate(const float t) const;

	Vec3f origin_;
	Vec3f direction_;
};

#endif