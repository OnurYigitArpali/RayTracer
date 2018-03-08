//
// Created by fatih on 16.11.2017.
//

#ifndef RAYTRACER2_ROTATION_H
#define RAYTRACER2_ROTATION_H

#include "vector3f.h"
namespace fst
{
    class Rotation
    {
    public:
        Rotation(const float angle, const math::Vector3f& val);
        float m_angle;
        math::Vector3f values;
    };
}


#endif //RAYTRACER2_ROTATION_H
