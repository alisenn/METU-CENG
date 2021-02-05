#pragma once

#include "scene.h"

namespace fst
{
    class Integrator
    {
    public:
        Integrator(const parser::Scene& parser);

        math::Vector3f renderPixel(const Ray& ray, int depth) const;
        void integrate() const;

    private:
        Scene m_scene;
    };
}