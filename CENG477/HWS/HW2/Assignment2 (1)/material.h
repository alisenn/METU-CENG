#pragma once

#include "hit_record.h"
#include "vector3f.h"

namespace fst
{
    class Material
    {
    public:
        Material(const math::Vector3f& ambient, const math::Vector3f& diffuse, const math::Vector3f& specular, const math::Vector3f& mirror, float phong_exponent);

        math::Vector3f computeBrdf(const math::Vector3f& wi, const math::Vector3f& wo, const math::Vector3f& normal) const;

        const math::Vector3f& get_ambient() const { return m_ambient; }
        const math::Vector3f& get_mirror() const { return m_mirror; }

    private:
        math::Vector3f m_ambient;
        math::Vector3f m_diffuse;
        math::Vector3f m_specular;
        math::Vector3f m_mirror;
        float m_phong_exponent;
    };
}