#pragma once

namespace fst
{
    namespace math
    {
        struct Vector4f
        {
            float x, y, z, w;

            Vector4f() = default;
            explicit Vector4f(float a)
                : x(a)
                , y(a)
                , z(a)
                , w(a)
            {}
            Vector4f(float a, float b, float c, float d)
                : x(a)
                , y(b)
                , z(c)
                , w(d)
            {}
        };
    }
}