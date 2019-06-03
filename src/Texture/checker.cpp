#include "Textures/checker.h"

Checker::Checker(TexturePtr odd, TexturePtr even) : odd_(std::move(odd)),
                                                    even_(std::move(even)) {}

Checker::~Checker() {}

Vec3f Checker::value(const float u, const float v, const Vec3f &p) const
{
    float sines = sin(10.0f * p[0]) * sin(10.0f * p[1]) * sin(10.0f * p[2]);
    if (sines < 0.0f)
        return odd_->value(u, v, p);
    else
        return even_->value(u, v, p);
}