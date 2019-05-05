#include "Renders/render.h"

Render::Render(const int widht,
               const int heigth,
               Camera &camera,
               Accelerator &accelerator,
               std::vector<Primitive::PrimitivePtr> &primitives) : width_{widht},
                                                                   height_{heigth},
                                                                   camera_{camera},
                                                                   accelerator_{accelerator},
                                                                   primitives_{primitives}
{

    accelerator_.build();

    buffer_.resize(width_, std::vector<Vec3f>(height_));
    for (int j = height_ - 1; j >= 0; j--)
        for (int i = 0; i < width_; i++)
            buffer_[i][j] = Vec3f(0.0f);
}

Render::~Render() {}