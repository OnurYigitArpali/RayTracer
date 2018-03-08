#pragma once

#include "triangle.h"
#include "transformation.h"
#include "jpeg.h"
#include "texture.h"

#include <vector>
#include <string>

namespace fst
{
    class Mesh : public Triangular
    {
    public:
        Mesh(const std::vector<Triangle>& triangles, int material_id, Texture texture);
        Mesh(std::vector<Triangle>&& triangles, int material_id, Texture texture);

        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const override;
        bool intersectShadowRay(const Ray& ray, float max_distance) const override;
        void texture_check(math::Vector3f intersection_point, Triangle triangle, HitRecord& hit_record, Texture texture) const;

    private:
	    std::vector<Triangle> m_triangles;
        int m_material_id;
        Texture m_texture;
    };
}
