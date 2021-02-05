#pragma once

#include "vector3f.h"

#include <memory>
#include <string>

namespace fst
{
    class Image
    {
    public:
        Image(int width, int height);

        void setPixel(int i, int j, const math::Vector3f& color);
        void save(const std::string& filepath) const;

    private:
        std::unique_ptr<unsigned char> m_image;
        int m_width;
        int m_height;
    };
}