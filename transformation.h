//
// Created by onur on 20.11.2017.
//

#ifndef RAYTRACER2_TRANSFORMATION_H
#define RAYTRACER2_TRANSFORMATION_H

#include "vector4f.h"
#include "vector3f.h"

namespace fst
{
    class Transformation
    {
    public:
        Transformation(){}
        static void scale(math::Vector3f& vertices, math::Vector3f& scale_value);
    };
}

#endif //RAYTRACER2_TRANSFORMATION_H

