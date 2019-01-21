#include "onb.h"

ONB::ONB()
{
}

ONB::~ONB()
{
}

void ONB::setFromUW(const glm::vec3 &u,
                    const glm::vec3 &w)
{
    u_ = u;
    w_ = w;
    v_ = glm::cross(w_, u_); //Since u and w are ortho, v is u x v (righthand rule)

    setBasisMatrix();
}

void ONB::setFromV(const glm::vec3 &v)
{
    v_ = v;

    if (fabs(v_.x) > fabs(v_.y))
        w_ = glm::normalize(glm::vec3{v_.z, 0.0, -v_.x});
    else
        w_ = glm::normalize(glm::vec3{0.0, -v_.z, v_.y});

    u_ = glm::cross(v_, w_);

    setBasisMatrix();
}

void ONB::setBasisMatrix()
{
    basis_[0] = u_;
    basis_[1] = v_;
    basis_[2] = w_;
}
