#ifndef RECORD_H
#define RECORD_H

#include "vec.h"

struct Record
{
  float t_;
  Vec3f point_;
  Vec3f normal_;
  size_t index_;
};

#endif