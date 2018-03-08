//
// Created by fatih on 16.11.2017.
//

#ifndef RAYTRACER2_TEXTURE_H
#define RAYTRACER2_TEXTURE_H

#include <string>
namespace fst
{
    class Texture
    {
    public:
        Texture(){};
        Texture(const std::string& image_n,const std::string& inter,const std::string &decal, const std::string& app);

        std::string image_name;
        std::string interpolation;
        std::string decal_mode;
        std::string appearance;
        int width, height;
        unsigned char* jpegImage;
    };
}


#endif //RAYTRACER2_TEXTURE_H
