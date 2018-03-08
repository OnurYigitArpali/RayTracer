#pragma once

#include <vector>
#include <string>
#include "vector3f.h"
#include "parser.h"
#include "texture.h"
#include "jpeg.h"
#include "hit_record.h"
#include "ray.h"


namespace fst
{
    class Ray;
    struct HitRecord;

    class Sphere
    {
    public:
        Sphere(const math::Vector3f center, float radius, int material_id, Texture texture);

        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const;
        bool intersectShadowRay(const Ray& ray, float max_distance) const;
        void texture_check(math::Vector3f intersection_point, HitRecord& hit_record) const;

    private:
        math::Vector3f m_center;
        float m_radius;
        int m_material_id;
        Texture m_texture;
    };
}