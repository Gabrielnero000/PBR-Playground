#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include <sstream>
#include <iomanip>
#include <chrono>
#include <random>
#include <omp.h>

#include "render.h"
#include "accelerator.h"

#define MIN_T 0.00001f
#define MAX_T 10000.0f
class PathTracer : public Render
{
public:
  PathTracer(Output &output,
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