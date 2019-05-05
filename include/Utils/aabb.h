#pragma once

#ifndef AABB_H
#define AABB_H

#include "ray.h"

class AABB
{
  public:
	AABB();
	AABB(const Vec3f &a, const Vec3f &b);

	Vec3f min() const;
	Vec3f max() const;

	Vec3f centroid() const;

	bool intersect(const Ray &ray, float t_min, float t_max) const;
	AABB static surroundingBox(const AABB &box_0, const AABB &box_1);

	Vec3f min_;
	Vec3f max_;
	Vec3f centroid_;
};

#endif