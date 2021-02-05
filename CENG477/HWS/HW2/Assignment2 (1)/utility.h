#pragma once

namespace fst
{
    namespace math
    {
        static float min(float a, float b)
        {
            return a < b ? a : b;
        }

        static float max(float a, float b)
        {
            return a > b ? a : b;
        }
    }
}