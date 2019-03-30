#ifndef RENDER_H
#define RENDER_H

/*******************************************************************************
    Class Render:

  - Core of the system. Responsable for the render process.

--------------------------------------------------------------------------------

  Variables:

  -  Output &output_;
    - Holds all necessary informations to generate the output image.

--------------------------------------------------------------------------------

  Methods:

  - Render(Output &output):
    - Constructor.

  - ~Render():
    - Deconstructor.

  - void integrate():
    - Do the render itselfs.

  - void test():
    - Tests and experiments (don't use).

********************************************************************************/

#include <sstream>
#include <iomanip>
#include <chrono>
#include <omp.h>

#include "output.h"
#include "camera.h"
#include "scene.h"
#include "material.h"
#include "lambertian.h"
#include "onb.h"

#define MIN_T 0.000001f
#define MAX_T 100000.0f
class Render
{
public:
  Render(Output &output,
         Scene &scene,
         Camera &camera,
         glm::vec3 &background_color_from,
         glm::vec3 &background_color_to,
         const int samples,
         const int ray_depth);
  ~Render();
  void integrate();
  void test();

private:
  glm::vec3 Color(const Ray &ray, Record &record, int depth);

  Output &output_;
  Scene &scene_;
  Camera &camera_;
  glm::vec3 background_color_from_;
  glm::vec3 background_color_to_;
  int samples_;
  int ray_depth_;
};

#endif