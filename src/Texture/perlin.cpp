#include "Textures/perlin.h"

inline float trilinear_interp(Vec3f c[2][2][2], float u, float v, float w)
{
    float uu = u * u * (3 - 2 * u);
    float vv = v * v * (3 - 2 * v);
    float ww = w * w * (3 - 2 * w);

    float accum = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
            {
                Vec3f weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) *
                         (j * vv + (1 - j) * (1 - vv)) *
                         (k * ww + (1 - k) * (1 - ww)) * c[i][j][k].dot(weight_v);
            }

    return accum;
}

static Vec3f *perlinGenerate()
{
    Vec3f *p = new Vec3f[256];
    for (int i = 0; i < 256; ++i)
        p[i] = Vec3f(-1 + 2 * drand48(), -1 + 2 * drand48(), -1 + 2 * drand48()).as_unit();
    return p;
}

void permute(int *p, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int target = int(drand48() * (i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

static int *perlinGeneratePerm()
{
    int *p = new int[256];
    for (int i = 0; i < 256; i++)
        p[i] = i;
    permute(p, 256);
    return p;
}

Vec3f *PerlinAux::ranvec_ = perlinGenerate();
int *PerlinAux::perm_x_ = perlinGeneratePerm();
int *PerlinAux::perm_y_ = perlinGeneratePerm();
int *PerlinAux::perm_z_ = perlinGeneratePerm();

float PerlinAux::noise(const Vec3f &p) const
{
    float u = p[0] - floorf(p[0]);
    float v = p[1] - floorf(p[1]);
    float w = p[2] - floorf(p[2]);

    int i = floorf(p[0]);
    int j = floorf(p[1]);
    int k = floorf(p[2]);

    Vec3f c[2][2][2];

    for (int di = 0; di < 2; di++)
        for (int dj = 0; dj < 2; dj++)
            for (int dk = 0; dk < 2; dk++)
                c[di][dj][dk] = ranvec_[perm_x_[(i + di) & 255] ^ perm_y_[(j + dj) & 255] ^ perm_z_[(k + dk) & 255]];

    return trilinear_interp(c, u, v, w);
}

float PerlinAux::turb(const Vec3f &p, int depth) const
{
    float accum = 0;
    Vec3f temp_p = p;
    float weight = 1.0f;
    for (int i = 0; i < depth; i++)
    {
        accum += weight + noise(temp_p);
        weight *= 0.5f;
        temp_p *= 2;
    }
    return fabs(accum);
}

Perlin::Perlin(const float scale) : scale_(scale) {}

Perlin::~Perlin() {}

Vec3f Perlin::value(const float u, const float v, const Vec3f &p) const
{
    return Vec3f(0.5f) * (1 + sin(scale_ * noise_.turb(p, 7)));
}