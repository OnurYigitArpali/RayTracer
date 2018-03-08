#include "material.h"
#include "vector3f.h"

namespace fst
{
    Material::Material(const math::Vector3f& ambient, const math::Vector3f& diffuse, const math::Vector3f& specular, const math::Vector3f& mirror, float phong_exponent)
        : m_ambient(ambient)
        , m_diffuse(diffuse)
        , m_specular(specular)
        , m_mirror(mirror)
        , m_phong_exponent(phong_exponent)
    {}

    math::Vector3f Material::computeBrdf(const math::Vector3f& wi, const math::Vector3f& wo, const math::Vector3f& normal, HitRecord& hit_Record) const
    {
        auto diffuse = math::max(math::dot(normal, wi), 0.0f);
        auto specular = std::pow(math::max(math::dot(math::normalize(wo + wi), normal), 0.0f), m_phong_exponent);

        if(hit_Record.text == true)
        {
            if (hit_Record.decal_mode == "replace_kd")
                return m_specular * specular +
                       math::Vector3f(hit_Record.texture_color.x / 255, hit_Record.texture_color.y / 255,
                                      hit_Record.texture_color.z / 255) * diffuse;
            else if(hit_Record.decal_mode == "blend_kd")
            {
                return m_specular * specular + (m_diffuse + math::Vector3f(hit_Record.texture_color.x / 255, hit_Record.texture_color.y / 255,
                                                                           hit_Record.texture_color.z / 255)) / 2 * diffuse;
            }
            else
            {
                return m_specular * specular;
            }
        }
        else
        {
            return m_specular * specular + m_diffuse * diffuse;
        }
    }
}