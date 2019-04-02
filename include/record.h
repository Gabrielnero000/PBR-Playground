#ifndef RECORD_H
#define RECORD_H

/*******************************************************************************
    struct Record:

  - Struct that holds an intersection's record.

--------------------------------------------------------------------------------

  Variables:

  - float t_:
    - Parameter t witch the intersection occurs.

  - glm::vec3 point_:
    - Point where the intersection occurs.

  - glm::vec3 normal_:
    - Normal vector to the intersection.

********************************************************************************/

#include <glm/glm.hpp>

struct Record
{
  float t_;
  glm::vec3 point_;
  glm::vec3 normal_;
  size_t index_;
};

#endif