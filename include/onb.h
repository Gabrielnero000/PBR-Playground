#ifndef ONB_H_
#define ONB_H_

/*******************************************************************************
    Class ONB:

  - Class for store operations involving Orthonormal Basis. Usefull when dealing
    with arbitrary cameras and multiple sampled rays, taking from the object 
    space to the world space abstracting some math.

--------------------------------------------------------------------------------

  Variables:

  - glm::mat3x3 basis_;
    - Stores the basis matrix in world space, responsable to take vectors in the
      object space to the world space. Composed by [u_ v_ w_] and initially is
      the canonic basis.

  - glm::vec3 u_;
    - Fisrt vector of the basis. Initially (1, 0, 0).

  - glm::vec3 v_;
    - Second vector of the basis. Initially (0, 1, 0).
    
  - glm::vec3 w_;
    - Third vector of the basis. Initially (0, 0, 1).

--------------------------------------------------------------------------------

  Methods:

  - ONB():
    - Constructor.

  - ~ONB():
    - Deconstructor.

  - void setFromV(const glm::vec3 &v):
    - Given the v vector, generate the u and w vectors for the basis.

  - void setFromUW(const glm::vec3 &u, const glm::vec3 &w):
    - Given the u and w vectors, generate the v vector for the basis.

  - void setBasisMatrix(void);
    - Updates the basis. 

********************************************************************************/

#include <glm/glm.hpp>

class ONB
{
public:
  ONB();

  ~ONB();

  void setFromV(const glm::vec3 &v);

  void setFromUW(const glm::vec3 &u,
                 const glm::vec3 &w);

  glm::mat3x3 basis_;
  glm::mat3x3 inverse_;

  glm::vec3 u_ = {1.0f, 0.0f, 0.0f};
  glm::vec3 v_ = {0.0f, 1.0f, 0.0f};
  glm::vec3 w_ = {0.0f, 0.0f, 1.0f};

private:
  void setBasisMatrix();
};

#endif
