#ifndef RENDER_H
#define RENDER_H

#include "accelerator.h"
#include "output.h"
#include "camera.h"

#define MIN_T 0.00001f
#define MAX_T 10000.0f

class Render
{
public:
  Render(Output &output,
         Camera &camera,
         Accelerator &accelerator,
         std::vector<Primitive::PrimitivePtr> &primitives);

  virtual ~Render();
  virtual void integrate() = 0;

  Output &output_;
  Camera &camera_;
  Accelerator &accelerator_;
  std::vector<Primitive::PrimitivePtr> &primitives_;
};

#endif