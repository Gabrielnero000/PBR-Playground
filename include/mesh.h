#pragma once

#ifndef MESH_H
#define MESH_H

#include "triangle.h"
#include <fstream>
#include <iostream>
#include <vector>

class Mesh : public Primitive
{
public:
  Mesh(Material *material,
       const std::string filename);
  ~Mesh();

  bool intersect(const Ray &ray,
                 float t_min,
                 float t_max,
                 Record &record) const;
                 
  bool boundingBox(float t0,
                   float t1,
                   AABB &box) const;

  std::vector<Triangle *> triangles_;
};

#endif