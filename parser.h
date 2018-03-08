#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <string>
#include <vector>

namespace parser
{
    //Notice that all the structures are as simple as possible
    //so that you are not enforced to adopt any style or design.

    struct Vec2f
    {
        float x, y;
    };

    struct Vec3f
    {
        float x, y, z;
    };

    struct Vec3i
    {
        int x, y, z;
    };

    struct Vec4f
    {
        float x, y, z, w;
    };

    struct Camera
    {
        Vec3f position;
        Vec3f gaze;
        Vec3f up;
        Vec4f near_plane;
        float near_distance;
        int image_width, image_height;
        std::string image_name;
    };

    struct PointLight
    {
        Vec3f position;
        Vec3f intensity;
    };

    struct Material
    {
        Vec3f ambient;
        Vec3f diffuse;
        Vec3f specular;
        Vec3f mirror;
        float phong_exponent;
    };

    struct Texture
    {
        std::string image_name;
        std::string interpolation;
        std::string decal_mode;
        std::string appearance;
    };

    struct Scaling
    {
        Vec3f value;
    };

    struct Translation
    {
        Vec3f value;
    };

    struct Rotation
    {
        float angle;
        Vec3f value;
    };

    struct Face
    {
        int v0_id;
        int v1_id;
        int v2_id;
    };

    struct Mesh
    {
        int material_id;
        std::vector<Face> faces;
        int texture_id;
        std::vector<std::string> transformations;
    };

    struct Triangle
    {
        int material_id;
        Face indices;
        int texture_id;
        std::vector<std::string> transformations;
    };

    struct Sphere
    {
        int material_id;
        int center_vertex_id;
        float radius;
        int texture_id;
        std::vector<std::string> transformations;
    };

    struct Mesh_Instance
    {
        int material_id;
        int mesh_id;
        int texture_id;
        std::vector<std::string> transformations;
    };

    struct Scene
    {
        //Data
        Vec3i background_color;
        float shadow_ray_epsilon;
        int max_recursion_depth;
        std::vector<Camera> cameras;
        Vec3f ambient_light;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<Texture> textures;
        std::vector<Scaling> scalings;
        std::vector<Translation> translations;
        std::vector<Rotation> rotations;
        std::vector<Vec3f> vertex_data;
        std::vector<Vec2f> tex_coord_data;
        std::vector<Mesh> meshes;
        std::vector<Triangle> triangles;
        std::vector<Sphere> spheres;
        std::vector<Mesh_Instance> mesh_instances;

        //Functions
        void loadFromXml(const std::string& filepath);
    };
}

#endif