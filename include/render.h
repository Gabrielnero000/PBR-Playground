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

#include "output.h"
#include "camera.h"
#include "scene.h"
#include "material.h"

#define MIN_T 0.0000001f
#define MAX_T 1000.0f
class Render
{
public:
  Render(Output &output,
         Scene &scene,
         Camera &camera,
         glm::vec3 &background_color_from,
         glm::vec3 &background_color_to,
         const int samples);
  ~Render();
  void integrate();
  void test();

private:
  glm::vec3 Color(const Ray &r, Record &record);
  Output &output_;
  Scene &scene_;
  Camera &camera_;
  glm::vec3 background_color_from_;
  glm::vec3 background_color_to_;
  int samples_;
};

#endif