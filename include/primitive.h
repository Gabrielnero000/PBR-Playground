#ifndef PRIMITIVE_H
#define PRIMITIVE_H

/*******************************************************************************
    Class Primitive:

  - Abstract class that represents a primitive. A primitive is an object witch
    rays can colide and can be grouped to form complex objects. Has an 
    PrimitiveUniquePtr to efficient deconstruction.

--------------------------------------------------------------------------------

  Variables:

  - glm::vec2 resolution:
    - Holds the resolution of the output image.

  - std::vector<std::vector<glm::vec3>> buffer_:
    - Matrix that holds the pixel data from the rendering process.

--------------------------------------------------------------------------------

  Methods:

  - Primitive():
    - Constructor.

  - virtual ~Primitive():
    - Deconstructor. 'Virtual' because it's an abstract class.

  - virtual bool intersect(const Ray &ray, float t_min, float t_max, Record &record) const = 0:
    - Given an Ray, tests if it intescets the primitive and stores the intersection's
      information (witch should be in the bounds [t_min, t_max]) in an Record.
      Every primitive has an different intersection algorithim, so must be
      overloaded

********************************************************************************/

#include <memory>
#include "ray.h"
#include "record.h"
#include "material.h"

class Primitive
{
public:
  typedef std::unique_ptr<Primitive> PrimitiveUniquePtr;
  //Material *material;

  Primitive();
  virtual ~Primitive();
  virtual bool intersect(const Ray &ray,
                                float t_min,
                                float t_max,
                                Record &record) const = 0;
};

#endif