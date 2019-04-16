#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>
#include <iostream>
#include "vec.h"

class Output
{
public:
  Output(const int width, const int height);
  ~Output();
  void save(const std::string filename);

  int width_;
  int height_;
  std::vector<std::vector<Vec3f>> buffer_;
};

#endif