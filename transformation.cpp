//
// Created by onur on 20.11.2017.
//

#include <vector>
#include "transformation.h"

namespace fst
{
    void Transformation::scale(math::Vector3f& vertices, math::Vector3f& scale_value) {
            vertices.x = scale_value.x * vertices.x;
            vertices.y = scale_value.y * vertices.y;
            vertices.z = scale_value.z * vertices.z;
        }

}
