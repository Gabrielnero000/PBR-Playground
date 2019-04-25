#include "triangle.h"
#include <iostream>

Triangle::Triangle(Material *material,
                   const Vec3f &v1,
                   const Vec3f &v2,
                   const Vec3f &v3) : Primitive::Primitive(material),
                                      v1_{v1},
                                      v2_{v2},
                                      v3_{v3},
                                      normal_{(v3 - v1).cross(v2 - v1).as_unit()}
{
#ifdef TRIANGLE_FAST

    const Vec3f C = v2_ - v1_;
    const Vec3f B = v3_ - v1_;

    if (fabs(normal_[0]) > fabs(normal_[1]))
        if (fabs(normal_[0]) > fabs(normal_[2]))
            k = 0;
        else
            k = 2;
    else if (fabs(normal_[1]) > fabs(normal_[2]))
        k = 1;
    else
        k = 2;

    const int u = modulo[k + 1];
    const int v = modulo[k + 2];

    const float normal_k = 1.0f / normal_[k];

    normal_u = normal_[u] * normal_k;
    normal_v = normal_[v] * normal_k;
    normal_d = normal_.dot(v1_) * normal_k;

    const float temp = 1.0f / (B[u] * C[v] - B[v] * C[u]);

    B_nu = B[u] * temp;
    B_nv = -B[v] * temp;

    C_nu = C[v] * temp;
    C_nv = -C[u] * temp;

#endif
}

/*  Solves the linear system: 

                                  [t]
        [- D, v2 - v1, v3 - v1] * [u] = O - v1
                                  [v]

    where:  v1, v2, v3 are the triangle's vertices
            D is the ray direction
            O is the ray origin
            t is the unknow parameter
            u, v are baricentric coordinates
*/

Triangle::~Triangle()
{
}

bool Triangle::intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const
{
#ifdef TRIANGLE_SMALL
    const Vec3f edge_1 = v2_ - v1_;
    const Vec3f edge_2 = v3_ - v1_;

    const Vec3f p_vec = glm::cross(ray.direction_, edge_2);
    float det = glm::dot(edge_1, p_vec);

    if (fabs(det) < t_min || fabs(det) > t_max)
        return false;

    det = 1.0f / det;

    const Vec3f t_vec = ray.origin_ - v1_;
    float u = glm::dot(t_vec, p_vec) * det;

    if (u < 0.0f || u > 1.0f)
    {
        return false;
    }

    const Vec3f q_vec = glm::cross(t_vec, edge_1);
    float v = glm::dot(ray.direction_, q_vec) * det;

    if (v < 0.0f || (u + v) > 1.0f)
    {
        return false;
    }

    record.t_ = glm::dot(edge_2, q_vec) * det;
    record.point_ = ray.evaluate(record.t_);
    record.normal_ = normal_;

    return true;

#else
#ifdef TRIANGLE_FAST

#define ku modulo[k + 1]
#define kv modulo[k + 2]

    const float nd = 1.0f / ((ray.direction_[k] +
                              normal_u * ray.direction_[ku] +
                              normal_v * ray.direction_[kv]) +
                             t_min); // Ensure that it's not zero

    const float f = (normal_d - ray.origin_[k] -
                     normal_u * ray.origin_[ku] -
                     normal_v * ray.origin_[kv]) *
                    nd;

    if (f < t_min || f > t_max)
        return false;

    const float hu = (ray.origin_[ku] + f * ray.direction_[ku] - v1_[ku]);
    const float hv = (ray.origin_[kv] + f * ray.direction_[kv] - v1_[kv]);

    const float beta = (hv * B_nu + hu * B_nv);

    if (beta < 0.0f)
        return false;

    const float gamma = (hu * C_nu + hv * C_nv);

    if (gamma < 0.0f)
        return false;

    if (beta + gamma > 1.0f)
        return false;

    record.t_ = f;
    record.point_ = ray.evaluate(record.t_);
    record.normal_ = normal_;
    record.material_ = material_;

    return true;
#endif
#endif
}

// TODO
bool Triangle::boundingBox(float t0,
                           float t1,
                           AABB &box) const
{
    return true;
}