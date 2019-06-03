#ifndef MAIN_H
#define MAIN_H

#include "Utils/utils.h"

#include "Cameras/ortho_camera.h"
#include "Cameras/pinhole_camera.h"

#include "Primitives/sphere.h"
#include "Primitives/triangle.h"

#include "Renders/path_tracer.h"

#include "Accelerators/no_accel.h"
#include "Accelerators/bvh.h"

#include "Materials/diffuse.h"
#include "Materials/specular.h"
#include "Materials/dieletric.h"
#include "Materials/emmiter.h"
#include "Materials/mix.h"

#include "Textures/color.h"
#include "Textures/checker.h"
#include "Textures/perlin.h"
#include "Textures/image.h"

#endif