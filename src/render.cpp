#include "render.h"

Render::Render(Output &output,
               Camera &camera,
               Accelerator &accelerator,
               std::vector<Primitive::PrimitivePtr> &primitives) : output_{output},
                                                                   camera_{camera},
                                                                   accelerator_{accelerator},
                                                                   primitives_{primitives}
{
    accelerator_.build();
}

Render::~Render() {}