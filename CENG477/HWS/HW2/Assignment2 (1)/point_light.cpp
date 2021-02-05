#include "point_light.h"

namespace fst
{
    PointLight::PointLight(const math::Vector3f& position, const math::Vector3f& intensity)
        : m_position(position)
        , m_intensity(intensity)
    {}
}