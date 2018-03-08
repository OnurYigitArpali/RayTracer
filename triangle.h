#pragma once

#include "triangular.h"
#include "vector3f.h"
#include "vector4f.h"
#include <vector>

namespace fst
{
    class Ray;
    struct HitRecord;

    class Triangle : public Triangular
    {
    public:
        Triangle(const math::Vector3f& v0, const math::Vector3f& edge1, const math::Vector3f& edge2,
                 const math::Vector3f normal, std::vector<math::Vector3f> vertices);

        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const override;
        bool intersectShadowRay(const Ray& ray, float max_distance) const override;

        math::Vector3f m_v0, m_edge1, m_edge2;
        math::Vector3f m_normal;
        std::vector<math::Vector3f> m_vertices;
    };
}
