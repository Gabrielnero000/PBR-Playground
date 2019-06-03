#include "Textures/color.h"

Color::Color(const Vec3f &color) : color_(color) {}

Color::~Color() {}

Vec3f Color::value(const float u, const float v, const Vec3f &p) const
{
    return color_;
}