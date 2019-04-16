#pragma once

#ifndef VEC_H
#define VEC_H

#include <math.h>
#include <iostream>

class Vec3f
{
  public:
    Vec3f() { v[0] = 0.0f, v[1] = 0.0f, v[2] = 0.0f; }
    Vec3f(float f) { v[0] = f, v[1] = f, v[2] = f; }
    Vec3f(float x, float y, float z) { v[0] = x, v[1] = y, v[2] = z; }

    float operator[](int i) const { return v[i]; }
    float &operator[](int i) { return v[i]; }

    const Vec3f &operator+() const { return *this; }
    Vec3f operator-() const { return Vec3f(-v[0], -v[1], -v[2]); }

    Vec3f &operator+=(const Vec3f &vec)
    {
        v[0] += vec[0], v[1] += vec[1], v[2] += vec[2];
        return *this;
    }
    Vec3f &operator-=(const Vec3f &vec)
    {
        v[0] -= vec[0], v[1] -= vec[1], v[2] -= vec[2];
        return *this;
    }
    Vec3f &operator*=(const Vec3f &vec)
    {
        v[0] *= vec[0], v[1] *= vec[1], v[2] *= vec[2];
        return *this;
    }
    Vec3f &operator/=(const Vec3f &vec)
    {
        v[0] /= vec[0], v[1] /= vec[1], v[2] /= vec[2];
        return *this;
    }

    Vec3f &operator+=(const float f)
    {
        v[0] += f, v[1] += f, v[2] += f;
        return *this;
    }
    Vec3f &operator-=(const float f)
    {
        v[0] -= f, v[1] -= f, v[2] -= f;
        return *this;
    }
    Vec3f &operator*=(const float f)
    {
        v[0] *= f, v[1] *= f, v[2] *= f;
        return *this;
    }
    Vec3f &operator/=(const float f)
    {
        const float k = 1.0f / f;
        v[0] *= k, v[1] *= k, v[2] *= k;
        return *this;
    }

    float length() const { return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }
    float squared_lenght() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
    void normalize()
    {
        const float k = 1.0f / length();
        v[0] *= k, v[1] *= k, v[2] *= k;
    }
    Vec3f as_unit() const
    {
        const float k = 1.0f / length();
        return Vec3f(v[0] * k, v[1] * k, v[2] * k);
    }

    float dot(const Vec3f &vec) const
    {
        return v[0] * vec[0] + v[1] * vec[1] + v[2] * vec[2];
    }

    Vec3f cross(const Vec3f &vec) const
    {
        return Vec3f(v[1] * vec[2] - v[2] * vec[1],
                     -(v[0] * vec[2] - v[2] * vec[0]),
                     v[0] * vec[1] - v[1] * vec[0]);
    }

  private:
    float v[3];
};

// ----------------------------------------------------------------------------------

inline Vec3f operator+(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline Vec3f operator-(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline Vec3f operator*(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline Vec3f operator/(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

inline Vec3f operator+(const Vec3f &v1, const float f)
{
    return Vec3f(v1[0] + f, v1[1] + f, v1[2] + f);
}

inline Vec3f operator-(const Vec3f &v1, const float f)
{
    return Vec3f(v1[0] - f, v1[1] - f, v1[2] - f);
}

inline Vec3f operator*(const Vec3f &v1, const float f)
{
    return Vec3f(v1[0] * f, v1[1] * f, v1[2] * f);
}

inline Vec3f operator/(const Vec3f &v1, const float f)
{
    return Vec3f(v1[0] / f, v1[1] / f, v1[2] / f);
}

inline Vec3f operator+(const float f, const Vec3f &v1)
{
    return Vec3f(f + v1[0], f + v1[1], f + v1[2]);
}

inline Vec3f operator-(const float f, const Vec3f &v1)
{
    return Vec3f(f - v1[0], f - v1[1], f - v1[2]);
}

inline Vec3f operator*(const float f, const Vec3f &v1)
{
    return Vec3f(f * v1[0], f * v1[1], f * v1[2]);
}

inline Vec3f operator/(const float f, const Vec3f &v1)
{
    return Vec3f(f / v1[0], f / v1[1], f / v1[2]);
}

// ----------------------------------------------------------------------------------

inline std::istream &operator>>(std::istream &is, Vec3f &t)
{
    is >> t[0] >> t[1] >> t[2];
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const Vec3f &t)
{
    os << t[0] << " " << t[1] << " " << t[2];
    return os;
}

#endif