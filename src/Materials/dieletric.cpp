#include "Materials/dieletric.h"

Dieletric::Dieletric(const Vec3f &emmiter,
                     const Vec3f &albedo,
                     float ref_idx) : Material::Material(emmiter, albedo),
                                      ref_idx_{ref_idx} {}

Dieletric::~Dieletric() {}

// Calculates the refracted vector
bool refract(const Vec3f &v,
             const Vec3f &n,
             float ni_over_nt,
             Vec3f &refracted)
{
    float dt = v.dot(n);
    float disc = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

    if (disc > 0.0f) // Refract, else TIR
    {
        refracted = ni_over_nt * (v - n * dt) - n * sqrtf(disc);
        return true;
    }

    return false;
}

float schlick(float cosine, float ref_idx)
{
    float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * powf((1.0f - cosine), 5);
}

bool Dieletric::scatter(const Ray &w_in,
                        const Record &record,
                        Vec3f &attenuation,
                        Ray &w_out) const
{
    attenuation = albedo_;

    Vec3f outward_normal;
    Vec3f reflected = reflect(w_in.direction_, record.normal_);
    Vec3f refracted;

    float ni_over_nt;
    float reflect_prob;
    float cosine;

    if (w_in.direction_.dot(record.normal_) > 0.0f)
    {
        outward_normal = -record.normal_;
        ni_over_nt = ref_idx_;
        cosine = ref_idx_ * w_in.direction_.dot(record.normal_);
    }
    else
    {
        outward_normal = record.normal_;
        ni_over_nt = 1.0f / ref_idx_;
        cosine = -(w_in.direction_.dot(record.normal_));
    }
    if (refract(w_in.direction_, outward_normal, ni_over_nt, refracted))
        reflect_prob = schlick(cosine, ref_idx_);
    else
        reflect_prob = 1.0f;

    std::minstd_rand gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    if (dist(gen) < reflect_prob)
        w_out = Ray(record.point_ + (reflected * 0.001f), reflected.as_unit());
    else
        w_out = Ray(record.point_ + (refracted * 0.001f), refracted.as_unit());

    return true;
}