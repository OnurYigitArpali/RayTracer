#pragma once

#include "camera.h"
#include "material.h"
#include "mesh.h"
#include "parser.h"
#include "point_light.h"
#include "ray.h"
#include "sphere.h"
#include "vector3f.h"
#include "texture.h"
#include "rotation.h"
#include "transformation.h"
#include "matrixInverse.h"

#include <vector>
#include <math.h>
#include <sstream>

namespace fst
{
    struct Scene
    {
        //Data
        std::vector<Camera> cameras;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<math::Vector3f> vertex_data;
        std::vector<math::Vector2f> tex_coord_data;
        std::vector<Mesh> meshes;
        std::vector<Sphere> spheres;
        std::vector<Texture> textures;
        std::vector<math::Vector3f> scalings;
        std::vector<math::Vector3f> translations;
        std::vector<Rotation> rotations;
        math::Vector3f background_color;
        math::Vector3f ambient_light;

        float shadow_ray_epsilon;
        int max_recursion_depth;

        //Functions
        void loadFromParser(const parser::Scene& parser);
        void sphere_transform(math::Vector3f& center,float& radius, std::vector<std::string> transformations);
        void triangle_transform(math::Vector3f& a, math::Vector3f& b, math::Vector3f& c, math::Vector3f& normal, std::vector<std::string> transformations);
        void multiply_3f(double M[], math::Vector3f& vector);
        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const;
        bool intersectShadowRay(const Ray& ray, float max_distance) const;

    };
}
