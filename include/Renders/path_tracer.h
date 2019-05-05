#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include <sstream>
#include <iomanip>
#include <chrono>
#include <random>
#include <omp.h>

#include "render.h"

class PathTracer : public Render
{
public:
  PathTracer(const int widht,
             const int height,
             Camera &camera,
             Accelerator &accelerator,
             std::vector<Primitive::PrimitivePtr> &primitives,
             Vec3f &background_color_from,
             Vec3f &background_color_to,
             const int samples,
             const int ray_depth);
  ~PathTracer();
  void integrate();

private:
  Vec3f Color(const Ray &ray, Record &record, int depth);

  Vec3f background_color_from_;
  Vec3f background_color_to_;
  int samples_;
  int ray_depth_;
};

#endif