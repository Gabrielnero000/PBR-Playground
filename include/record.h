#pragma once

#ifndef RECORD_H
#define RECORD_H

class Material;

#include "vec.h"
#include "material.h"

struct Record
{
	float t_;
	Vec3f point_;
	Vec3f normal_;
	Material *material_;
};

#endif