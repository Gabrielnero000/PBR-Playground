#ifndef ONB_H_
#define ONB_H_

#include "vec.h"

class ONB
{
public:
  ONB();

  ~ONB();

  void setFromV(const Vec3f &v);

  void setFromUW(const Vec3f &u,
                 const Vec3f &w);

  Vec3f applyONB(const Vec3f &v) const;

  Vec3f u_ = {1.0f, 0.0f, 0.0f};
  Vec3f v_ = {0.0f, 1.0f, 0.0f};
  Vec3f w_ = {0.0f, 0.0f, 1.0f};
};

#endif
