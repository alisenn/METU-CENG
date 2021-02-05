#include "hit_record.h"
#include "triangle.h"
#include "ray.h"

namespace fst
{
    Triangle::Triangle(const math::Vector3f& v0, const math::Vector3f& edge1, const math::Vector3f& edge2)
        : m_v0(v0)
        , m_edge1(edge1)
        , m_edge2(edge2)
        , m_normal(math::normalize(math::cross(edge1, edge2)))
    {}

    bool Triangle::intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const
    {
        //Möller-Trumbore algorithm
        auto pvec = math::cross(ray.get_direction(), m_edge2);
        auto inv_det = 1.0f / math::dot(m_edge1, pvec);

        auto tvec = ray.get_origin() - m_v0;
        auto w1 = math::dot(tvec, pvec) * inv_det;

        if (w1 < 0.0f || w1 > 1.0f)
        {
            return false;
        }

        auto qvec = math::cross(tvec, m_edge1);
        auto w2 = math::dot(ray.get_direction(), qvec) * inv_det;

        if (w2 < 0.0f || (w1 + w2) > 1.0f)
        {
            return false;
        }

        auto distance = math::dot(m_edge2, qvec) * inv_det;
        if (distance > 0.0f && distance < max_distance)
        {
            //Fill the intersection record.
            hit_record.normal = m_normal;
            hit_record.distance = distance;

            return true;
        }
        return false;
    }

    bool Triangle::intersectShadowRay(const Ray& ray, float max_distance) const
    {
        //Möller-Trumbore algorithm
        auto pvec = math::cross(ray.get_direction(), m_edge2);
        auto inv_det = 1.0f / math::dot(m_edge1, pvec);

        auto tvec = ray.get_origin() - m_v0;
        auto w1 = math::dot(tvec, pvec) * inv_det;

        if (w1 < 0.0f || w1 > 1.0f)
        {
            return false;
        }

        auto qvec = math::cross(tvec, m_edge1);
        auto w2 = math::dot(ray.get_direction(), qvec) * inv_det;

        if (w2 < 0.0f || (w1 + w2) > 1.0f)
        {
            return false;
        }

        auto distance = math::dot(m_edge2, qvec) * inv_det;
        return distance > 0.0f && distance < max_distance;
    }
}
