#include "camera.h"

namespace fst
{
    Camera::Camera(const math::Vector3f& position, const math::Vector3f& direction, const math::Vector3f& world_up,
        const math::Vector4f& screen_coordinates, const math::Vector2f& screen_resolution, const std::string& image_name,
        float near_distance)
        : m_screen_coordinates(screen_coordinates)
        , m_position(position)
        , m_gaze(-direction)
        , m_up(world_up)
        , m_screen_resolution(screen_resolution)
        , m_image_name(image_name)
        , m_near_distance(near_distance)
    {
        m_gaze = math::normalize(m_gaze);
        m_right = math::normalize(math::cross(m_up, m_gaze));
        m_up = math::normalize(math::cross(m_gaze, m_right));

        m_coeff.x = (m_screen_coordinates.y - m_screen_coordinates.x) / m_screen_resolution.x;
        m_coeff.y = (m_screen_coordinates.w - m_screen_coordinates.z) / m_screen_resolution.y;
    }
}