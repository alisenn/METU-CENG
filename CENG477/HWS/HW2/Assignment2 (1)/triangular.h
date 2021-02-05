#pragma once

namespace fst
{
    class Ray;
    struct HitRecord;

    class Triangular
    {
    public:
        virtual ~Triangular() {}
        virtual bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const = 0;
        virtual bool intersectShadowRay(const Ray& ray, float max_distance) const = 0;
    };
}
