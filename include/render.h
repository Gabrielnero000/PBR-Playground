#ifndef RENDER_H
#define RENDER_H

#include <sstream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include <random>

#include "output.h"
#include "camera.h"
#include "scene.h"
#include "material.h"
#include "lambertian.h"
#include "onb.h"

#define MIN_T 0.00001f
#define MAX_T 10000.0f
class Render
{
public:
  Render(Output &output,
         Scene &scene,
         Camera &camera,
         Vec3f &background_color_from,
         Vec3f &background_color_to,
         const int samples,
         const int ray_depth);
  ~Render();
  void integrate();
  void test();

private:
  Vec3f Color(const Ray &ray, Record &record, int depth);

  Output &output_;
  Scene &scene_;
  Camera &camera_;
  Vec3f background_color_from_;
  Vec3f background_color_to_;
  int samples_;
  int ray_depth_;
};

#endif