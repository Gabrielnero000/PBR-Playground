#ifndef OUTPUT_H
#define OUTPUT_H

/*******************************************************************************
    Class Output:

  - Responsable for generate the output image from the render results in PPM 
    format on the specified resolution.

--------------------------------------------------------------------------------

  Variables:

  - glm::vec2 resolution:
    - Holds the resolution of the output image.

  - std::vector<std::vector<glm::vec3>> buffer_:
    - Matrix that holds the pixel data from the rendering process.

--------------------------------------------------------------------------------

  Methods:

  - Output(glm::vec2 resolution):
    - Constructor.

  - ~Output():
    - Deconstructor.

  - const bool save():
    - Saves the image into the disk as "output.ppm". Returns true if suceeds to
      save.

********************************************************************************/

#include <vector>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

class Output
{
public:
  Output(const glm::vec2 resolution);
  ~Output();
  void save();

  glm::vec2 resolution_;
  std::vector<std::vector<glm::vec3>> buffer_;
};

#endif