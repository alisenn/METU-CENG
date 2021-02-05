#include "image.h"
#include "ppm.h"

namespace fst
{
    Image::Image(int width, int height)
        : m_image(new unsigned char[width * height * 3])
        , m_width(width)
        , m_height(height)
    {}

    void Image::setPixel(int i, int j, const math::Vector3f& color)
    {
        int index = (j * m_width + i) * 3;
        auto ptr = m_image.get();
        ptr[index] = static_cast<unsigned char>(color.x);
        ptr[index + 1] = static_cast<unsigned char>(color.y);
        ptr[index + 2] = static_cast<unsigned char>(color.z);
    }

    void Image::save(const std::string& filepath) const
    {
        write_ppm(filepath.c_str(), m_image.get(), m_width, m_height);
    }
}