#ifndef ONB_H_
#define ONB_H_

#include <glm/glm.hpp>

class ONB
{
  public:
    ONB(void);

    void setFromV(const glm::vec3 &v);

    void setFromUW(const glm::vec3 &u,
                   const glm::vec3 &w);

    glm::mat3x3 basis_;

    glm::vec3 u_ = {1.0f, 0.0f, 0.0f};
    glm::vec3 v_ = {0.0f, 1.0f, 0.0f};
    glm::vec3 w_ = {0.0f, 0.0f, 1.0f};

  private:
    void setBasisMatrix(void);
};

#endif
