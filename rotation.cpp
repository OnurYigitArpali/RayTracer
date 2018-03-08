//
// Created by fatih on 16.11.2017.
//

#include "rotation.h"
namespace fst
{
    Rotation::Rotation(const float angle, const math::Vector3f& val)
        : values(val)
        , m_angle(angle)
    {}
}
