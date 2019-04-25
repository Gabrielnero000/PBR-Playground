#pragma once

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include <random>

class Lambertian : public Material
{
  public:
	Lambertian(const Vec3f &emmiter, const Vec3f &albedo);
	~Lambertian();

	bool scatter(const Ray &w_in,
				 const Record &record,
				 Vec3f &attenuation,
				 Ray &w_out) const;

	Vec3f albedo_;
};

#endif