#include "triangle.h"

Triangle::Triangle(const glm::vec3 &v1,
                   const glm::vec3 &v2,
                   const glm::vec3 &v3) : v1_{v1},
                                          v2_{v2},
                                          v3_{v3}
{
#ifdef TRIANGLE_WALD
    const glm::vec3 edge_1 = v2_ - v1_;
    const glm::vec3 edge_2 = v3_ - v1_;
    const glm::vec3 normal = glm::cross(edge_1, edge_2);

    if (fabs(normal.x) > fabs(normal.y))
        if (fabs(normal.x) > fabs(normal.z))
            acc.k = 0;
        else
            acc.k = 2;
    else if (fabs(normal.y) > fabs(normal.z))
        acc.k = 1;
    else
        acc.k = 2;

    const int u = modulo[acc.k + 1];
    const int v = modulo[acc.k + 2];

    acc.normal_u = normal[u] / normal[acc.k];
    acc.normal_v = normal[v] / normal[acc.k];
    acc.normal_d = glm::dot(v1_, (normal / normal[acc.k]));

    const float temp = 1.0f / (edge_2[u] * edge_1[v] - edge_2[v] * edge_1[u]);

    acc.edge1_nu = edge_1[v] / temp;
    acc.edge1_nv = -edge_1[u] / temp;
    acc.edge1_d = (edge_1[u] * v1_[v] - edge_1[v] * v1_[u]) / temp;

    acc.edge2_nu = -edge_2[v] / temp;
    acc.edge2_nv = edge_2[u] / temp;
    acc.edge2_d = (edge_2[v] * v1_[u] - edge_2[u] * v1_[v]) / temp;

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

inline bool Triangle::intersect(const Ray &ray,
                                float t_min,
                                float t_max,
                                Record &record) const
{
#ifdef TRIANGLE_MOLLER
    const glm::vec3 edge_1 = v2_ - v1_;
    const glm::vec3 edge_2 = v3_ - v1_;

    const glm::vec3 p_vec = glm::cross(ray.direction_, edge_2);
    float det = glm::dot(edge_1, p_vec);

    if (fabs(det) < t_min || fabs(det) > t_max)
        return false;

    det = 1.0f / det;

    const glm::vec3 t_vec = ray.origin_ - v1_;
    float u = glm::dot(t_vec, p_vec) * det;

    if (u < 0.0f || u > 1.0f)
    {
        return false;
    }

    const glm::vec3 q_vec = glm::cross(t_vec, edge_1);
    float v = glm::dot(ray.direction_, q_vec) * det;

    if (v < 0.0f || (u + v) > 1.0f)
    {
        return false;
    }

    record.t_ = glm::dot(edge_2, q_vec) * det;
    record.point_ = ray.evaluate(record.t_);
    record.normal_ = glm::normalize(glm::cross(edge_1, edge_2));

    return true;

#else
#ifdef TRIANGLE_WALD

    const int ku = modulo[acc.k + 1];
    const int kv = modulo[acc.k + 2];

    const float nd = 1.0f / (ray.direction_[acc.k] +
                             acc.normal_u * ray.direction_[ku] +
                             acc.normal_v * ray.direction_[kv]);

    const float f = (acc.normal_d - ray.origin_[acc.k] -
                     acc.normal_u * ray.origin_[ku] -
                     acc.normal_v * ray.origin_[kv]) *
                    nd;
    if (f < t_min || f > t_max)
        return false;

    const float hu = (ray.origin_[ku] + f * ray.direction_[ku]);
    const float hv = (ray.origin_[kv] + f * ray.direction_[kv]);

    const float beta = (hu * acc.edge2_nu + hv * acc.edge2_nv + acc.edge2_d);

    if (beta < 0.0f)
        return false;

    const float gamma = (hu * acc.edge1_nu + hv * acc.edge1_nv + acc.edge1_d);

    if (gamma < 0.0f)
        return false;

    if (beta + gamma > 1.0f)
        return false;

    record.t_ = f;
    record.point_ = ray.evaluate(record.t_);
    record.normal_ = glm::normalize(glm::cross(v2_ - v1_, v3_ - v1_));

    return true;
#endif
#endif
}