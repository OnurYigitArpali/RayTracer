#include <iostream>
#include "scene.h"

# define PI 3.14159265

namespace fst
{

    void Scene::multiply_3f(double M[], math::Vector3f& vector)
    {
        math::Vector3f temp;

        temp.x = M[0] * vector.x + M[1] * vector.y + M[2] * vector.z + M[3];
        temp.y = M[4] * vector.x + M[5] * vector.y + M[6] * vector.z + M[7];
        temp.z = M[8] * vector.x + M[9] * vector.y + M[10] * vector.z + M[11];

        vector.x = temp.x;
        vector.y = temp.y;
        vector.z = temp.z;

    }

    void Scene::sphere_transform(math::Vector3f& center,float &radius, std::vector<std::string> transformations)
    {
        int invert_flag = 0;
        double M[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double Current_Transform[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double inv[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double t_inv[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double rotate_M[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double rotate_transpose_M[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double rotate_X[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        for(int i=0; i<transformations.size(); i++)
        {
            std::stringstream ss(&transformations[i][1]);
            int index;
            ss >> index;

            if(transformations[i][0] == 's')
            {
                Current_Transform[0]  = scalings[index -1].x;
                Current_Transform[5]  = scalings[index -1].y;
                Current_Transform[10] = scalings[index -1].z;

                if(scalings[index-1].x == scalings[index-1].y && scalings[index-1].x == scalings[index-1].z)
                {
                    multiply(Current_Transform, M);
                    radius = radius * scalings[index - 1].x;
                }
                Current_Transform[0]  = 1;
                Current_Transform[5]  = 1;
                Current_Transform[10] = 1;
                invert_flag = 1;
            }
            else if(transformations[i][0] == 't')
            {
                Current_Transform[3]  = translations[index -1].x;
                Current_Transform[7]  = translations[index -1].y;
                Current_Transform[11] = translations[index -1].z;

                multiply(Current_Transform, M);

                Current_Transform[3]  = 0;
                Current_Transform[7]  = 0;
                Current_Transform[11] = 0;
            }
            else if(transformations[i][0] == 'r')
            {
                float temp, min = std::min(rotations[index-1].values.x, std::min(rotations[index-1].values.y,rotations[index-1].values.z));
                math::Vector3f v;
                math::Vector3f w;
                math::Vector3f u;
                v = rotations[index-1].values;
                u = rotations[index-1].values;
                if(u.x == min)
                {
                    v.x = 0;
                    temp = v.y;
                    v.y = -v.z;
                    v.z = temp;
                }
                else if(u.y == min)
                {
                    v.y = 0;
                    temp = v.x;
                    v.x = -v.z;
                    v.z = temp;
                }
                else
                {
                    v.z = 0;
                    temp = v.y;
                    v.y = -v.x;
                    v.x = temp;
                }
                w = math::cross(u,v);

                rotate_M[0] = u.x; rotate_M[1] = u.y; rotate_M[2] = u.z; rotate_M[3] = 0;
                rotate_M[4] = v.x; rotate_M[5] = v.y; rotate_M[6] = v.z; rotate_M[7] = 0;
                rotate_M[8] = w.x; rotate_M[9] = w.y; rotate_M[10] = w.z; rotate_M[11] = 0;

                invert(rotate_M,rotate_transpose_M);

                rotate_X[5] = cos(rotations[index-1].m_angle * PI / 180.0); rotate_X[6] = -sin(rotations[index-1].m_angle * PI / 180.0);
                rotate_X[9] = sin(rotations[index-1].m_angle * PI / 180.0); rotate_X[10] = cos(rotations[index-1].m_angle * PI / 180.0);

                multiply(rotate_M,Current_Transform);

                multiply(rotate_X,Current_Transform);

                multiply(rotate_transpose_M,Current_Transform);

                multiply(Current_Transform, M);


                for(int i=0; i<16; i++)
                {
                    Current_Transform[i] = 0;
                }
                Current_Transform[0]=1; Current_Transform[5]=1; Current_Transform[10]=1; Current_Transform[15]=1;
            }
        }

        multiply_3f(M,center);


    }

    void Scene::triangle_transform(math::Vector3f& a, math::Vector3f& b, math::Vector3f& c, math::Vector3f& normal, std::vector<std::string> transformations)
    {
        int invert_flag=0;
        double M[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double Current_Transform[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double inv[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double t_inv[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double rotate_M[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double rotate_transpose_M[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        double rotate_X[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };

        for(int i=0; i<transformations.size(); i++)
        {
            std::stringstream ss(&transformations[i][1]);
            int index;
            ss >> index;

            if(transformations[i][0] == 's')
            {
                Current_Transform[0]  = scalings[index -1].x;
                Current_Transform[5]  = scalings[index -1].y;
                Current_Transform[10] = scalings[index -1].z;

                multiply(Current_Transform, M);

                Current_Transform[0]  = 1;
                Current_Transform[5]  = 1;
                Current_Transform[10] = 1;
                invert_flag = 1;
            }
            else if(transformations[i][0] == 't')
            {
                Current_Transform[3]  = translations[index -1].x;
                Current_Transform[7]  = translations[index -1].y;
                Current_Transform[11] = translations[index -1].z;

                multiply(Current_Transform, M);

                Current_Transform[3]  = 0;
                Current_Transform[7]  = 0;
                Current_Transform[11] = 0;
            }
            else if(transformations[i][0] == 'r')
            {
                float temp, min = std::min(rotations[index-1].values.x, std::min(rotations[index-1].values.y,rotations[index-1].values.z));
                math::Vector3f v;
                math::Vector3f w;
                math::Vector3f u;
                v = rotations[index-1].values;
                u = rotations[index-1].values;
                if(u.x == min)
                {
                    v.x = 0;
                    temp = v.y;
                    v.y = -v.z;
                    v.z = temp;
                }
                else if(u.y == min)
                {
                    v.y = 0;
                    temp = v.x;
                    v.x = -v.z;
                    v.z = temp;
                }
                else
                {
                    v.z = 0;
                    temp = v.y;
                    v.y = -v.x;
                    v.x = temp;
                }
                w = math::cross(u,v);

                rotate_M[0] = u.x; rotate_M[1] = u.y; rotate_M[2] = u.z; rotate_M[3] = 0;
                rotate_M[4] = v.x; rotate_M[5] = v.y; rotate_M[6] = v.z; rotate_M[7] = 0;
                rotate_M[8] = w.x; rotate_M[9] = w.y; rotate_M[10] = w.z; rotate_M[11] = 0;

                invert(rotate_M,rotate_transpose_M);

                rotate_X[5] = cos(rotations[index-1].m_angle * PI / 180.0); rotate_X[6] = -sin(rotations[index-1].m_angle * PI / 180.0);
                rotate_X[9] = sin(rotations[index-1].m_angle * PI / 180.0); rotate_X[10] = cos(rotations[index-1].m_angle * PI / 180.0);

                multiply(rotate_M,Current_Transform);

                multiply(rotate_X,Current_Transform);

                multiply(rotate_transpose_M,Current_Transform);

                multiply(Current_Transform, M);


                for(int i=0; i<16; i++)
                {
                    Current_Transform[i] = 0;
                }
                Current_Transform[0]=1; Current_Transform[5]=1; Current_Transform[10]=1; Current_Transform[15]=1;
            }
        }

        if(invert_flag)
        {
            invert(M, inv);
            transpose(inv, t_inv);
        }

        multiply_3f(M,a);
        multiply_3f(M,b);
        multiply_3f(M,c);
        normal = math::normalize(math::cross(b-a,c-a));

        if(invert_flag)
            multiply_3f(t_inv,normal);
    }

    void Scene::loadFromParser(const parser::Scene& parser)
    {
        for (auto& camera : parser.cameras)
        {
            cameras.push_back(Camera(
                math::Vector3f(camera.position.x, camera.position.y, camera.position.z),
                math::Vector3f(camera.gaze.x, camera.gaze.y, camera.gaze.z),
                math::Vector3f(camera.up.x, camera.up.y, camera.up.z),
                math::Vector4f(camera.near_plane.x, camera.near_plane.y, camera.near_plane.z, camera.near_plane.w),
                math::Vector2f(camera.image_width, camera.image_height),
                camera.image_name,
                camera.near_distance));
        }

        for (auto& pointlight : parser.point_lights)
        {
            point_lights.push_back(PointLight(
                math::Vector3f(pointlight.position.x, pointlight.position.y, pointlight.position.z),
                math::Vector3f(pointlight.intensity.x, pointlight.intensity.y, pointlight.intensity.z)));
        }

        for (auto& material : parser.materials)
        {
            materials.push_back(Material(
                math::Vector3f(material.ambient.x, material.ambient.y, material.ambient.z),
                math::Vector3f(material.diffuse.x, material.diffuse.y, material.diffuse.z),
                math::Vector3f(material.specular.x, material.specular.y, material.specular.z),
                math::Vector3f(material.mirror.x, material.mirror.y, material.mirror.z),
                material.phong_exponent));
        }

        for (auto& texture : parser.textures)
        {
            textures.push_back(Texture(
                    texture.image_name,
                    texture.interpolation,
                    texture.decal_mode,
                    texture.appearance ));
        }

        for (auto& scaling : parser.scalings)
        {
            scalings.push_back(math::Vector3f(scaling.value.x, scaling.value.y, scaling.value.z));
        }

        for (auto& translation : parser.translations)
        {
            translations.push_back(math::Vector3f(translation.value.x, translation.value.y, translation.value.z));
        }

        for (auto& rotation : parser.rotations)
        {
            rotations.push_back(Rotation(rotation.angle,
                                         math::Vector3f(rotation.value.x, rotation.value.y, rotation.value.z)));
        }

        for (auto& tex_coor : parser.tex_coord_data)
        {
            tex_coord_data.push_back(math::Vector2f(tex_coor.x, tex_coor.y));
        }

        for (auto& vertex : parser.vertex_data)
        {
            vertex_data.push_back(math::Vector3f(vertex.x, vertex.y, vertex.z));
        }

        for (auto& mesh : parser.meshes)
        {
            std::vector<Triangle> triangles;
            math::Vector3f normal;

            for (auto& face : mesh.faces)
            {
                std::vector<math::Vector3f> vertices;
                math::Vector3f new_a,new_b,new_c;
                new_a.x = vertex_data[face.v0_id - 1].x; new_a.y = vertex_data[face.v0_id - 1].y; new_a.z = vertex_data[face.v0_id - 1].z;
                new_b.x = vertex_data[face.v1_id - 1].x; new_b.y = vertex_data[face.v1_id - 1].y; new_b.z = vertex_data[face.v1_id - 1].z;
                new_c.x = vertex_data[face.v2_id - 1].x; new_c.y = vertex_data[face.v2_id - 1].y; new_c.z = vertex_data[face.v2_id - 1].z;

                triangle_transform(new_a,new_b,new_c,normal,mesh.transformations);

                vertices.push_back(new_a);
                vertices.push_back(new_b);
                vertices.push_back(new_c);

                triangles.push_back(Triangle(
                        new_a,
                        new_b - new_a,
                        new_c - new_a, normal, vertices));
                vertices.clear();
            }
            if(mesh.texture_id)
                meshes.push_back(Mesh(std::move(triangles), mesh.material_id, textures[mesh.texture_id-1]));
            else
                meshes.push_back(Mesh(std::move(triangles), mesh.material_id, Texture()));
        }

        for (auto& triangle : parser.triangles)
        {
            std::vector<Triangle> triangles;

            math::Vector3f normal;
            std::vector<math::Vector3f> vertices;

            math::Vector3f new_a,new_b,new_c;
            new_a.x = vertex_data[triangle.indices.v0_id - 1].x; new_a.y = vertex_data[triangle.indices.v0_id - 1].y; new_a.z = vertex_data[triangle.indices.v0_id - 1].z;
            new_b.x = vertex_data[triangle.indices.v1_id - 1].x; new_b.y = vertex_data[triangle.indices.v1_id - 1].y; new_b.z = vertex_data[triangle.indices.v1_id - 1].z;
            new_c.x = vertex_data[triangle.indices.v2_id - 1].x; new_c.y = vertex_data[triangle.indices.v2_id - 1].y; new_c.z = vertex_data[triangle.indices.v2_id - 1].z;

            triangle_transform(new_a,new_b,new_c,normal,triangle.transformations);

            vertices.push_back(new_a);
            vertices.push_back(new_b);
            vertices.push_back(new_c);

            triangles.push_back(Triangle(
                    new_a,
                    new_b - new_a,
                    new_c - new_a, normal, vertices));

            vertices.clear();

            if(triangle.texture_id)
                meshes.push_back(Mesh(std::move(triangles), triangle.material_id, textures[triangle.texture_id-1]));
            else
                meshes.push_back(Mesh(std::move(triangles), triangle.material_id, Texture()));
        }

        for (auto& sphere : parser.spheres)
        {
            math::Vector3f new_center;
            float new_radius = sphere.radius;
            new_center.x = vertex_data[sphere.center_vertex_id - 1].x;
            new_center.y = vertex_data[sphere.center_vertex_id - 1].y;
            new_center.z = vertex_data[sphere.center_vertex_id - 1].z;

            sphere_transform(new_center,new_radius, sphere.transformations);

            if(sphere.texture_id)
                spheres.push_back(Sphere(new_center, new_radius, sphere.material_id, textures[sphere.texture_id-1]));
            else
                spheres.push_back(Sphere(new_center, new_radius, sphere.material_id, Texture()));

        }

        for (auto& mesh_instance : parser.mesh_instances)
        {
            std::vector<Triangle> triangles;
            math::Vector3f normal;

            std::vector<std::string> new_transformations = parser.meshes[mesh_instance.mesh_id-1].transformations;
            new_transformations.insert( new_transformations.end(), mesh_instance.transformations.begin(), mesh_instance.transformations.end() );

            for (auto& face : parser.meshes[mesh_instance.mesh_id-1].faces)
            {

                math::Vector3f new_a,new_b,new_c;
                std::vector<math::Vector3f> vertices;

                new_a.x = vertex_data[face.v0_id - 1].x; new_a.y = vertex_data[face.v0_id - 1].y; new_a.z = vertex_data[face.v0_id - 1].z;
                new_b.x = vertex_data[face.v1_id - 1].x; new_b.y = vertex_data[face.v1_id - 1].y; new_b.z = vertex_data[face.v1_id - 1].z;
                new_c.x = vertex_data[face.v2_id - 1].x; new_c.y = vertex_data[face.v2_id - 1].y; new_c.z = vertex_data[face.v2_id - 1].z;

                triangle_transform(new_a,new_b,new_c,normal,new_transformations);

                vertices.push_back(new_a);
                vertices.push_back(new_b);
                vertices.push_back(new_c);

                triangles.push_back(Triangle(
                        new_a,
                        new_b - new_a,
                        new_c - new_a, normal, vertices));
                vertices.clear();

            }
            if(mesh_instance.texture_id)
                meshes.push_back(Mesh(std::move(triangles), mesh_instance.material_id, textures[mesh_instance.texture_id-1]));
            else
                meshes.push_back(Mesh(std::move(triangles), mesh_instance.material_id, Texture()));
        }

        background_color = math::Vector3f(parser.background_color.x, parser.background_color.y, parser.background_color.z);
        ambient_light = math::Vector3f(parser.ambient_light.x, parser.ambient_light.y, parser.ambient_light.z);
        shadow_ray_epsilon = parser.shadow_ray_epsilon;
        max_recursion_depth = parser.max_recursion_depth;
    }

    bool Scene::intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const
    {
        HitRecord temp;
        float min_distance = max_distance;
        for (auto& sphere : spheres)
        {
            if (sphere.intersect(ray, temp, min_distance))
            {
                min_distance = temp.distance;
                hit_record = temp;
            }
        }

        for (auto& mesh : meshes)
        {
            if (mesh.intersect(ray, temp, min_distance))
            {
                min_distance = temp.distance;
                hit_record = temp;
            }
        }

        return min_distance != max_distance;
    }

    bool Scene::intersectShadowRay(const Ray& ray, float max_distance) const
    {
        for (auto& sphere : spheres)
        {
            if (sphere.intersectShadowRay(ray, max_distance))
            {
                return true;
            }
        }


        for (auto& mesh : meshes)
        {
            if (mesh.intersectShadowRay(ray, max_distance))
            {
		        return true;
            }
        }

	return false;
    }
}
