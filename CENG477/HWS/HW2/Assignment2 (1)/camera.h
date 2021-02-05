#pragma once

#include "ray.h"
#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"

#include <string>

namespace fst
{
    class Camera
    {
    public:
        Camera(const math::Vector3f& position, const math::Vector3f& direction, const math::Vector3f& up,
            const math::Vector4f& screen_coordinates, const math::Vector2f& screen_resolution,
            const std::string& image_name, float distance);

        Ray castPrimayRay(float x, float y) const
        {
            auto dir = -m_near_distance * m_gaze +
                (m_screen_coordinates.x + m_coeff.x * (x + 0.5f)) * m_right + (m_screen_coordinates.w - m_coeff.y * (y + 0.5f)) * m_up;

            return Ray(m_position, math::normalize(dir));
        }

        const math::Vector2f& get_screen_resolution() const { return m_screen_resolution; }
        const std::string& get_image_name() const { return m_image_name; }

    private:
        math::Vector4f m_screen_coordinates;
        math::Vector3f m_position;
        math::Vector3f m_gaze;
        math::Vector3f m_up;
        math::Vector3f m_right;
        math::Vector2f m_coeff;
        math::Vector2f m_screen_resolution;
        std::string m_image_name;
        float m_near_distance;
    };
}