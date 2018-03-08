#include <iostream>
#include "sphere.h"

#define PI 3.14159265

namespace fst
{
    Sphere::Sphere(const math::Vector3f center, float radius, int material_id, Texture texture)
        : m_center(center)
        , m_radius(radius)
        , m_material_id(material_id)
        , m_texture(texture)
    {}

    bool Sphere::intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const
    {
        //geometrical approach
        auto e = m_center - ray.get_origin();
        auto a = math::dot(e, ray.get_direction());
        auto x = m_radius * m_radius + a * a - math::dot(e, e);

        if (x < 0.0f)
        {
            return false;
        }

        auto distance = a - sqrtf(x);
        if (distance > 0.0f && distance < max_distance)
        {

            hit_record.distance = distance;
            hit_record.normal = math::normalize(ray.getPoint(hit_record.distance) - m_center);
            hit_record.material_id = m_material_id;
            auto intersection_point = ray.getPoint(hit_record.distance);
            if(m_texture.image_name != "" )
            {
                hit_record.text = true;
                hit_record.decal_mode = (m_texture.decal_mode);
                texture_check(intersection_point, hit_record);
            }

            return true;
        }
        return false;
    }

    bool Sphere::intersectShadowRay(const Ray& ray, float max_distance) const
    {
        //geometrical approach
        auto e = m_center - ray.get_origin();
        auto a = math::dot(e, ray.get_direction());
        auto x = m_radius * m_radius + a * a - math::dot(e, e);

        if (x < 0.0f)
        {
            return false;
        }

        auto distance = a - sqrtf(x);
        return distance > 0.0f && distance < max_distance;
    }

    void Sphere::texture_check(math::Vector3f intersection_point, HitRecord& hit_record) const
    {
        double u, v, fi, theta, p, q, dx, dy;
        int i_inter, j_inter, pixel_start;
        intersection_point.x = intersection_point.x - m_center.x;
        intersection_point.y = intersection_point.y - m_center.y;
        intersection_point.z = intersection_point.z - m_center.z;

        theta = acos(intersection_point.y / m_radius) * 180.0 / PI;
        fi = atan2(intersection_point.z , intersection_point.x) * 180.0 / PI;
        u = (-fi + 180.0)/(360.0);
        v = theta / 180.0;

        if(m_texture.appearance.compare("clamp") == 0)
        {
            u = ( u > 1 ? 1 : ( u < 0 ? 0 : u));
            v = ( v > 1 ? 1 : ( v < 0 ? 0 : v));
        }
        else
        {
            u = u - floor(u);
            v = v - floor(v);
        }

        double i = u * m_texture.width;
        double j = v * m_texture.height;
        if(m_texture.interpolation.compare("nearest") == 0)
        {
            i_inter = (int) round(i);
            j_inter = (int) round(j);

            pixel_start = (j_inter*m_texture.width + i_inter)*3 ;

            hit_record.texture_color.x = m_texture.jpegImage[pixel_start];
            hit_record.texture_color.y = m_texture.jpegImage[pixel_start+1];
            hit_record.texture_color.z = m_texture.jpegImage[pixel_start+2];
        }
        else
        {
            p = floor(i);
            q = floor(j);
            dx = i - p;
            dy = j - q;
            math::Vector3f color(0,0,0);

            pixel_start = (int)(q*m_texture.width + p)*3 ;

            color.x = m_texture.jpegImage[pixel_start]*(1-dx)*(1-dy);
            color.y = m_texture.jpegImage[pixel_start+1]*(1-dx)*(1-dy);
            color.z = m_texture.jpegImage[pixel_start+2]*(1-dx)*(1-dy);

            pixel_start = (int)(q*m_texture.width + p+1)*3 ;

            color.x += m_texture.jpegImage[pixel_start]*(dx)*(1-dy);
            color.y += m_texture.jpegImage[pixel_start+1]*(dx)*(1-dy);
            color.z += m_texture.jpegImage[pixel_start+2]*(dx)*(1-dy);

            pixel_start = (int)((q+1)*m_texture.width + p)*3 ;

            color.x += m_texture.jpegImage[pixel_start]*(1-dx)*(dy);
            color.y += m_texture.jpegImage[pixel_start+1]*(1-dx)*(dy);
            color.z += m_texture.jpegImage[pixel_start+2]*(1-dx)*(dy);

            pixel_start = (int)((q+1)*m_texture.width + p+1)*3 ;

            color.x += m_texture.jpegImage[pixel_start]*(dx)*(dy);
            color.y += m_texture.jpegImage[pixel_start+1]*(dx)*(dy);
            color.z += m_texture.jpegImage[pixel_start+2]*(dx)*(dy);

            hit_record.texture_color = color;
        }


    }
}