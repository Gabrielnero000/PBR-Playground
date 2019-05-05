#include "Utils/onb.h"

ONB::ONB()
{
}

ONB::~ONB()
{
}

void ONB::setFromUW(const Vec3f &u,
                    const Vec3f &w)
{
    u_ = u;
    w_ = w;
    v_ = w_.cross(u_); //Since u and w are ortho, v is u x v (righthand rule)
}

void ONB::setFromV(const Vec3f &v)
{
    v_ = v;

    if (fabs(v_[0]) > fabs(v_[1]))
        w_ = Vec3f(v_[2], 0.0, -v_[0]).as_unit();
    else
        w_ = Vec3f(0.0, -v_[2], v_[1]).as_unit();

    u_ = v_.cross(w_);
}

Vec3f ONB::applyONB(const Vec3f &vec) const
{
    return Vec3f(u_[0] * vec[0] + v_[0] * vec[1] + w_[0] * vec[2],
                 u_[1] * vec[0] + v_[1] * vec[1] + w_[1] * vec[2],
                 u_[2] * vec[0] + v_[2] * vec[1] + w_[2] * vec[2]);
}
