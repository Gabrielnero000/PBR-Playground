#include "Textures/image.h"

Image::Image(unsigned char *pixels, int A, int B) : data_(pixels), nx_(A), ny_(B) {}

Image::~Image() {}

Vec3f Image::value(float u, float v, const Vec3f &p) const
{
    int i = (u)*nx_;
    int j = (1 - v) * ny_ - 0.001f;

    if (i < 0)
        i = 0;
    if (j < 0)
        j = 0;
    if (i > nx_ - 1)
        i = nx_ - 1;
    if (j > ny_ - 1)
        j = ny_ - 1;

    float r = int(data_[3 * i + 3 * nx_ * j]) / 225.0f;
    float g = int(data_[3 * i + 3 * nx_ * j + 1]) / 225.0f;
    float b = int(data_[3 * i + 3 * nx_ * j + 2]) / 225.0f;

    //std::cout << r << ", " << g << ", " << b << std::endl;

    return Vec3f(r, g, b);
}