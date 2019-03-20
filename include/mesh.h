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
  typedef std::unique_ptr<Triangle> TriangleUniquePtr;

  Mesh(MaterialUniquePtr material,
       const std::string filename);
  ~Mesh();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;

  std::vector<TriangleUniquePtr> triangles_;
};

#endif