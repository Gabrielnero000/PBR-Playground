#ifndef MESH_H
#define MESH_H

#include "primitive.h"
#include "triangle.h"
#include <fstream>
#include <iostream>
#include <vector>

class Mesh : public Primitive
{
public:
  Mesh(const std::string filename);
  ~Mesh();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  std::vector<Triangle*> triangles_;
};

#endif