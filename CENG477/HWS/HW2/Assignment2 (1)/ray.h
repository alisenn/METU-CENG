#pragma once

#include "vector3f.h"

namespace fst
{
    class Ray
    {
    public:
        Ray(const math::Vector3f& origin, const math::Vector3f& direction);

        math::Vector3f getPoint(float distance) const { return m_origin + m_direction * distance; }

        const math::Vector3f& get_origin() const { return m_origin; }
        const math::Vector3f& get_direction() const { return m_direction; }

    private:
        math::Vector3f m_origin;
        math::Vector3f m_direction;
    };
}