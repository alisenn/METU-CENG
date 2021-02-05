#pragma once

#include "utility.h"
#include <cmath>

namespace fst
{
    namespace math
    {
        struct Vector3f
        {
            float x, y, z;

            Vector3f() = default;
            explicit Vector3f(float a)
                : x(a)
                , y(a)
                , z(a)
            {}
            Vector3f(float a, float b, float c)
                : x(a)
                , y(b)
                , z(c)
            {}

            Vector3f operator - () const
            {
                return Vector3f(-x, -y, -z);
            }

            Vector3f operator + (const Vector3f& vec) const
            {
                return Vector3f(x + vec.x, y + vec.y, z + vec.z);
            }

            Vector3f operator - (const Vector3f& vec) const
            {
                return Vector3f(x - vec.x, y - vec.y, z - vec.z);
            }

            Vector3f operator * (const Vector3f& vec) const
            {
                return Vector3f(x * vec.x, y * vec.y, z * vec.z);
            }

            Vector3f operator / (const Vector3f& vec) const
            {
                return Vector3f(x / vec.x, y / vec.y, z / vec.z);
            }

            float operator [] (int i) const
            {
                return (&x)[i];
            }
        };

        static Vector3f operator * (const Vector3f& vec, float scalar)
        {
            return Vector3f(vec.x * scalar, vec.y * scalar, vec.z * scalar);
        }

        static Vector3f operator * (float scalar, const Vector3f& vec)
        {
            return Vector3f(vec.x * scalar, vec.y * scalar, vec.z * scalar);
        }

        static Vector3f operator / (const Vector3f& vec, float scalar)
        {
            return Vector3f(vec.x / scalar, vec.y / scalar, vec.z / scalar);
        }

        static Vector3f operator / (float scalar, const Vector3f& vec)
        {
            return Vector3f(scalar / vec.x, scalar / vec.y, scalar / vec.z);
        }

        static float length(const Vector3f& vec)
        {
            return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
        }

        static float dot(const Vector3f& vec1, const Vector3f& vec2)
        {
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        }

        static Vector3f cross(const Vector3f& vec1, const Vector3f& vec2)
        {
            return Vector3f(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
        }

        static Vector3f normalize(const Vector3f& vec)
        {
            return vec / length(vec);
        }

        static Vector3f min(const Vector3f& vec1, const Vector3f& vec2)
        {
            return Vector3f(math::min(vec1.x, vec2.x), math::min(vec1.y, vec2.y), math::min(vec1.z, vec2.z));
        }

        static Vector3f max(const Vector3f& vec1, const Vector3f& vec2)
        {
            return Vector3f(math::max(vec1.x, vec2.x), math::max(vec1.y, vec2.y), math::max(vec1.z, vec2.z));
        }

        static Vector3f clamp(const Vector3f& vec, float min, float max)
        {
            return Vector3f(math::min(math::max(vec.x, min), max), math::min(math::max(vec.y, min), max), math::min(math::max(vec.z, min), max));
        }

        static Vector3f reflect(const Vector3f& vec, const Vector3f& normal)
        {
            return vec - normal * dot(normal, vec) * 2.0f;
        }
    }
}
