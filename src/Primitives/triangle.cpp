#include "Primitives/triangle.h"

Triangle::Triangle(Material::MaterialPtr material,
                   const std::string &id,
                   const Vec3f &v1,
                   const Vec3f &v2,
                   const Vec3f &v3,
                   const Vec3f &n1,
                   const Vec3f &n2,
                   const Vec3f &n3,
                   const float tx_1,
                   const float ty_1,
                   const float tx_2,
                   const float ty_2,
                   const float tx_3,
                   const float ty_3,
                   const bool smooth) : Primitive::Primitive(std::move(material), id),
                                        v1_(v1),
                                        v2_(v2),
                                        v3_(v3),
                                        n1_(n1),
                                        n2_(n2),
                                        n3_(n3),
                                        tx_1_(tx_1),
                                        ty_1_(ty_1),
                                        tx_2_(tx_2),
                                        ty_2_(ty_2),
                                        tx_3_(tx_3),
                                        ty_3_(ty_3),
                                        smooth_(smooth),
                                        normal_(((v2 - v1).cross(v3 - v1)).as_unit())
{
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
}

Triangle::~Triangle() {}

bool Triangle::intersect(const Ray &ray,
                         float t_min,
                         float t_max,
                         Record &record) const
{

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
    record.point_ = ray.evaluate(f);

    if (smooth_)
        record.normal_ = (n1_ * (1.0f - beta - gamma) + n2_ * beta + n3_ * gamma).as_unit();
    else
        record.normal_ = normal_;

    record.u_ = tx_1_ * (1.0f - beta - gamma) + tx_2_ * beta + tx_3_ * gamma;
    record.v_ = ty_1_ * (1.0f - beta - gamma) + ty_2_ * beta + ty_3_ * gamma;

    return true;
}

bool Triangle::boundingBox(AABB &box) const
{
    box = AABB();

    float x_min = v1_[0] < v2_[0] ? (v1_[0] < v3_[0] ? v1_[0] : v3_[0]) : (v2_[0] < v3_[0] ? v2_[0] : v3_[0]);
    float y_min = v1_[1] < v2_[1] ? (v1_[1] < v3_[1] ? v1_[1] : v3_[1]) : (v2_[1] < v3_[1] ? v2_[1] : v3_[1]);
    float z_min = v1_[2] < v2_[2] ? (v1_[2] < v3_[2] ? v1_[2] : v3_[2]) : (v2_[2] < v3_[2] ? v2_[2] : v3_[2]);

    float x_max = v1_[0] > v2_[0] ? (v1_[0] > v3_[0] ? v1_[0] : v3_[0]) : (v2_[0] > v3_[0] ? v2_[0] : v3_[0]);
    float y_max = v1_[1] > v2_[1] ? (v1_[1] > v3_[1] ? v1_[1] : v3_[1]) : (v2_[1] > v3_[1] ? v2_[1] : v3_[1]);
    float z_max = v1_[2] > v2_[2] ? (v1_[2] > v3_[2] ? v1_[2] : v3_[2]) : (v2_[2] > v3_[2] ? v2_[2] : v3_[2]);

    box.min_ = Vec3f(x_min - 0.0001f, y_min - 0.0001f, z_min - 0.0001f);
    box.max_ = Vec3f(x_max + 0.0001f, y_max + 0.0001f, z_max + 0.0001f);
    box.centroid_ = (1.0f / 3.0f) * (v1_ + v2_ + v3_);
    return true;
}