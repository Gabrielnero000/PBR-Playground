#pragma once

#ifndef RECORD_H
#define RECORD_H

#include "vec.h"

class Material;

struct Record
{
  float t_;
  Vec3f point_;
  Vec3f normal_;
  Material *material_;
};

#endif