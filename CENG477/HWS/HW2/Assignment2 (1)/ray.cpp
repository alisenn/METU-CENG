#include "ray.h"

namespace fst
{
    Ray::Ray(const math::Vector3f& origin, const math::Vector3f& direction)
        : m_origin(origin)
        , m_direction(direction)
    {}
}