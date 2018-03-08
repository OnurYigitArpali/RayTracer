#include "parser.h"
#include "tinyxml2.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

void parser::Scene::loadFromXml(const std::string& filepath)
{
    tinyxml2::XMLDocument file;
    std::stringstream stream;

    auto res = file.LoadFile(filepath.c_str());
    if (res)
    {
        throw std::runtime_error("Error: The xml file cannot be loaded.");
    }

    auto root = file.FirstChild();
    if (!root)
    {
        throw std::runtime_error("Error: Root is not found.");
    }

    //Get BackgroundColor
    auto element = root->FirstChildElement("BackgroundColor");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0 0 0" << std::endl;
    }
    stream >> background_color.x >> background_color.y >> background_color.z;

    //Get ShadowRayEpsilon
    element = root->FirstChildElement("ShadowRayEpsilon");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0.001" << std::endl;
    }
    stream >> shadow_ray_epsilon;

    //Get MaxRecursionDepth
    element = root->FirstChildElement("MaxRecursionDepth");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0" << std::endl;
    }
    stream >> max_recursion_depth;

    //Get Cameras
    element = root->FirstChildElement("Cameras");
    element = element->FirstChildElement("Camera");
    Camera camera;
    while (element)
    {
        auto child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Gaze");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Up");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearPlane");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearDistance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageResolution");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageName");
        stream << child->GetText() << std::endl;

        stream >> camera.position.x >> camera.position.y >> camera.position.z;
        stream >> camera.gaze.x >> camera.gaze.y >> camera.gaze.z;
        stream >> camera.up.x >> camera.up.y >> camera.up.z;
        stream >> camera.near_plane.x >> camera.near_plane.y >> camera.near_plane.z >> camera.near_plane.w;
        stream >> camera.near_distance;
        stream >> camera.image_width >> camera.image_height;
        stream >> camera.image_name;

        cameras.push_back(camera);
        element = element->NextSiblingElement("Camera");
    }

    //Get Lights
    element = root->FirstChildElement("Lights");
    auto child = element->FirstChildElement("AmbientLight");
    stream << child->GetText() << std::endl;
    stream >> ambient_light.x >> ambient_light.y >> ambient_light.z;
    element = element->FirstChildElement("PointLight");
    PointLight point_light;
    while (element)
    {
        child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Intensity");
        stream << child->GetText() << std::endl;

        stream >> point_light.position.x >> point_light.position.y >> point_light.position.z;
        stream >> point_light.intensity.x >> point_light.intensity.y >> point_light.intensity.z;

        point_lights.push_back(point_light);
        element = element->NextSiblingElement("PointLight");
    }

    //Get Materials
    element = root->FirstChildElement("Materials");
    element = element->FirstChildElement("Material");
    Material material;
    while (element)
    {
        child = element->FirstChildElement("AmbientReflectance");
        stream << child->GetText() << std::endl;
        stream >> material.ambient.x >> material.ambient.y >> material.ambient.z;

        child = element->FirstChildElement("DiffuseReflectance");
        stream << child->GetText() << std::endl;
        stream >> material.diffuse.x >> material.diffuse.y >> material.diffuse.z;

        child = element->FirstChildElement("SpecularReflectance");
        stream << child->GetText() << std::endl;
        stream >> material.specular.x >> material.specular.y >> material.specular.z;

        child = element->FirstChildElement("MirrorReflectance");
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> material.mirror.x >> material.mirror.y >> material.mirror.z;
        }
        else
        {
            material.mirror.x = 0; material.mirror.y = 0; material.mirror.z = 0;
        }
        child = element->FirstChildElement("PhongExponent");
        stream << child->GetText() << std::endl;
        stream >> material.phong_exponent;

        materials.push_back(material);
        element = element->NextSiblingElement("Material");
    }

    //Get Textures
    element = root->FirstChildElement("Textures");
    if (element)
        element = element->FirstChildElement("Texture");
    Texture texture;
    while (element)
    {
        child = element->FirstChildElement("ImageName");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Interpolation");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("DecalMode");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Appearance");
        stream << child->GetText() << std::endl;

        stream >> texture.image_name;
        stream >> texture.interpolation;
        stream >> texture.decal_mode;
        stream >> texture.appearance;

        textures.push_back(texture);
        element = element->NextSiblingElement("Texture");
    }
    stream.clear();

    //Get Translation
    element = root->FirstChildElement("Transformations");
    if (element)
        child = element->FirstChildElement("Translation");
    Translation translation;
    while (element && child)
    {
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> translation.value.x >> translation.value.y >> translation.value.z;

            translations.push_back(translation);
        }
        child = child->NextSiblingElement("Translation");
    }
    stream.clear();

    //Get Scaling
    element = root->FirstChildElement("Transformations");
    if (element)
        child = element->FirstChildElement("Scaling");
    Scaling scaling;
    while (element && child)
    {
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> scaling.value.x >> scaling.value.y >> scaling.value.z;
            scalings.push_back(scaling);
        }
        child = child->NextSiblingElement("Scaling");
    }
    stream.clear();

    //Get Rotation
    element = root->FirstChildElement("Transformations");
    if (element)
        child = element->FirstChildElement("Rotation");
    Rotation rotation;
    while (element && child)
    {
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> rotation.angle >> rotation.value.x >> rotation.value.y >> rotation.value.z;

            rotations.push_back(rotation);
        }
        child = child->NextSiblingElement("Rotation");
    }
    stream.clear();

    //Get VertexData
    element = root->FirstChildElement("VertexData");
    stream << element->GetText() << std::endl;
    Vec3f vertex;
    while (!(stream >> vertex.x).eof())
    {
        stream >> vertex.y >> vertex.z;
        vertex_data.push_back(vertex);
    }
    stream.clear();

    //Get tex_coord_data
    element = root->FirstChildElement("TexCoordData");
    if (element)
    {
        stream << element->GetText() << std::endl;
        Vec2f tex_coord;
        while (!(stream >> tex_coord.x).eof()) {
            stream >> tex_coord.y;
            tex_coord_data.push_back(tex_coord);
        }
    }
    stream.clear();

    //Get Meshes
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Mesh");
    Mesh mesh;
    while (element)
    {

        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> mesh.material_id;

        child = element->FirstChildElement("Texture");
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> mesh.texture_id;
        }
        else
        {
            mesh.texture_id = 0;
        }

        child = element->FirstChildElement("Transformations");
        if (child)
        {
            stream << child->GetText() << std::endl;
            std::string trans;
            while (!(stream >> trans).eof()) {
                mesh.transformations.push_back(trans);
            }
        }
        stream.clear();

        child = element->FirstChildElement("Faces");
        stream << child->GetText() << std::endl;
        Face face;
        while (!(stream >> face.v0_id).eof())
        {
            stream >> face.v1_id >> face.v2_id;
            mesh.faces.push_back(face);
        }
        stream.clear();

        meshes.push_back(mesh);
        mesh.faces.clear();
        mesh.transformations.clear();
        element = element->NextSiblingElement("Mesh");
    }
    stream.clear();

    //Get Triangles
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Triangle");
    Triangle triangle;
    while (element)
    {
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> triangle.material_id;

        child = element->FirstChildElement("Indices");
        stream << child->GetText() << std::endl;
        stream >> triangle.indices.v0_id >> triangle.indices.v1_id >> triangle.indices.v2_id;

        child = element->FirstChildElement("Texture");
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> triangle.texture_id;
        }
        else
        {
            triangle.texture_id = 0;
        }
        stream.clear();

        child = element->FirstChildElement("Transformations");
        if (child)
        {
            stream << child->GetText() << std::endl;
            std::string trans;
            while (!(stream >> trans).eof()) {
                triangle.transformations.push_back(trans);
            }
        }
        stream.clear();

        triangles.push_back(triangle);
        triangle.transformations.clear();
        element = element->NextSiblingElement("Triangle");
    }
    stream.clear();

    //Get Spheres
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Sphere");
    Sphere sphere;
    while (element) {
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> sphere.material_id;

        child = element->FirstChildElement("Center");
        stream << child->GetText() << std::endl;
        stream >> sphere.center_vertex_id;

        child = element->FirstChildElement("Radius");
        stream << child->GetText() << std::endl;
        stream >> sphere.radius;

        child = element->FirstChildElement("Texture");
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> sphere.texture_id;
        }
        else
        {
            sphere.texture_id = 0;
        }
        stream.clear();

        child = element->FirstChildElement("Transformations");
        if (child)
        {
            stream << child->GetText() << std::endl;
            std::string trans;
            while (!(stream >> trans).eof()) {
                sphere.transformations.push_back(trans);
            }
        }
        stream.clear();

        spheres.push_back(sphere);
        sphere.transformations.clear();
        element = element->NextSiblingElement("Sphere");
    }

    //Get Mesh_Instances
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("MeshInstance");
    Mesh_Instance mesh_instance;
    while (element)
    {
        auto attribute = element->IntAttribute("baseMeshId",0);
        mesh_instance.mesh_id = attribute;

        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> mesh_instance.material_id;

        child = element->FirstChildElement("Texture");
        if (child)
        {
            stream << child->GetText() << std::endl;
            stream >> mesh_instance.texture_id;
        }
        else
        {
            mesh_instance.texture_id = 0;
        }
        stream.clear();

        child = element->FirstChildElement("Transformations");
        if (child)
        {
            stream << child->GetText() << std::endl;
            std::string trans;
            while (!(stream >> trans).eof()) {
                mesh_instance.transformations.push_back(trans);
            }
        }
        stream.clear();

        mesh_instances.push_back(mesh_instance);
        mesh_instance.transformations.clear();
        element = element->NextSiblingElement("MeshInstance");
    }
    stream.clear();
}
