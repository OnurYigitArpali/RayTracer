#pragma once

#include "vector3f.h"
#include "string"
// object type Sphere:0 Triangle:1

namespace fst
{
    struct HitRecord
    {
        math::Vector3f normal;
        float distance;
        int material_id;
        double texture_i;
        double texture_j;
        bool text = false;
        std::string decal_mode;
        math::Vector3f texture_color;
    };
}