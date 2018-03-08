#include "mesh.h"
#include "hit_record.h"
#include "ray.h"
#include "vector3f.h"

namespace fst
{
    Mesh::Mesh(const std::vector<Triangle>& triangles, int material_id, Texture texture)
    {
        m_triangles = triangles;
        m_material_id = material_id;

        m_texture.image_name = texture.image_name;
        m_texture.interpolation = texture.interpolation;
        m_texture.decal_mode = texture.decal_mode;
        m_texture.appearance = texture.appearance;
    }

    Mesh::Mesh(std::vector<Triangle>&& triangles, int material_id, Texture texture)
    {
        m_triangles = triangles;
        m_material_id = material_id;

        m_texture.image_name = texture.image_name;
        m_texture.interpolation = texture.interpolation;
        m_texture.decal_mode = texture.decal_mode;
        m_texture.appearance = texture.appearance;
    }

    bool Mesh::intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const
    {
        HitRecord temp;
        float min_distance = max_distance;
        if(m_texture.image_name == "")
        {
            for (auto &triangle : m_triangles) {
                if (triangle.intersect(ray, temp, min_distance) && math::dot(temp.normal, ray.get_direction()) < 0.0f) {
                    min_distance = temp.distance;
                    hit_record = temp;
                    hit_record.material_id = m_material_id;
                }
            }
        }
        else
        {
            for (auto &triangle : m_triangles) {
                if (triangle.intersect(ray, temp, min_distance) && math::dot(temp.normal, ray.get_direction()) < 0.0f) {
                    min_distance = temp.distance;
                    hit_record = temp;
                    hit_record.material_id = m_material_id;
//                    auto intersection_point = ray.getPoint(hit_record.distance);
//                    texture_check(intersection_point, triangle, hit_record, m_texture);
                }
            }
        }
        return min_distance != max_distance;
    }

    bool Mesh::intersectShadowRay(const Ray& ray, float max_distance) const
    {
        for (auto& triangle : m_triangles)
        {
            if (triangle.intersectShadowRay(ray, max_distance))
            {
		        return true;
            }
        }

	    return false;
    }

    void Mesh::texture_check(math::Vector3f intersection_point, Triangle triangle, HitRecord& hit_record, Texture texture) const{

        // Read it back to a different array
        const char * texture_name = texture.image_name.c_str();

        int w, h;
        read_jpeg_header(texture_name, w, h);
        unsigned char* jpegImage = new unsigned char [w * h * 3];
        read_jpeg(texture_name, jpegImage, w, h);

        double alpha,beta;
//
//
//        double dx = w;
//        double dy = h;
//        double Ux = 0, Uy = 0, Uz = 0;
//        double Vx = 0, Vy = 0, Vz = 0;
//        double v2x = 0, v2y = 0, v2z = 0;
//        double distp = 0;
//        Ux = triangle.m_vertices[2].x - triangle.m_vertices[1].x;
//        Uy = triangle.m_vertices[2].y - triangle.m_vertices[1].y;
//        Uz = triangle.m_vertices[2].z - triangle.m_vertices[1].z;
//        v2x = intersection_point.x - triangle.m_vertices[1].x;
//        v2y = intersection_point.y - triangle.m_vertices[1].y;
//        v2z = intersection_point.z - triangle.m_vertices[1].z;
//        distp = math::length(math::Vector3f(triangle.m_vertices[1].x-intersection_point.x,
//                                            triangle.m_vertices[1].y-intersection_point.y,
//                                            triangle.m_vertices[1].z-intersection_point.z));
//        Vx = triangle.m_vertices[0].x - triangle.m_vertices[1].x;
//        Vy = triangle.m_vertices[0].y - triangle.m_vertices[1].y;
//        Vz = triangle.m_vertices[0].z - triangle.m_vertices[1].z;
//        double dU = math::length(math::Vector3f(Ux, Uy, Uz));
//        double dV = math::length(math::Vector3f(Vx, Vy, Vz));
//        tAlgebra.Normalize(ref Ux, ref Uy, ref Uz);
//        tAlgebra.Normalize(ref v2x, ref v2y, ref v2z);
//        double cost = tAlgebra.Dot3(Ux, Uy, Uz, v2x, v2y, v2z);
//        double t = Math.Acos(cost);
//        double distY=0, distX=0;
//        distY = dU - distp * Math.Cos(t);
//        distX = dV - distp * Math.Sin(t);
//        double x1 = 0;
//        double y1 = 0;
//        y1 = tAlgebra.GetCoord(0, dU, tmp3y * dy, tmp2y * dy, distY);
//        x1 = tAlgebra.GetCoord(0, dV, tmp1x * dx, tmp2x * dx, distX);
    }
}
