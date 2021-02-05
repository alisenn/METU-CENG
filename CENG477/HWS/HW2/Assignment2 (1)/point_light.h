#pragma once

#include "vector3f.h"

namespace fst
{
    class PointLight
    {
    public:
        PointLight(const math::Vector3f& position, const math::Vector3f& intensity);

        math::Vector3f computeRadiance(float distance) const { return m_intensity / (distance * distance); }

        const math::Vector3f& get_position() const { return m_position; }
        const math::Vector3f& get_intensity() const { return m_intensity; }

    private:
        math::Vector3f m_position;
        math::Vector3f m_intensity;
    };
}