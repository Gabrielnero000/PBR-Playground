#ifndef RENDER_H
#define RENDER_H

#include "Accelerators/accelerator.h"
#include "Cameras/camera.h"

#define MIN_T 0.0001f
#define MAX_T 10000.0f

class Render
{
public:
  Render(const int widht,
         const int heigth,
         Camera &camera,
         Accelerator &accelerator,
         std::vector<Primitive::PrimitivePtr> &primitives);

  virtual ~Render();
  virtual void integrate() = 0;

  Camera &camera_;
  Accelerator &accelerator_;
  std::vector<Primitive::PrimitivePtr> &primitives_;
  std::vector<std::vector<Vec3f>> buffer_;
  const int width_;
  const int height_;
};

#endif