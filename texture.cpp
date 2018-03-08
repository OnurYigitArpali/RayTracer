//
// Created by fatih on 16.11.2017.
//

#include "texture.h"
#include "jpeg.h"

namespace fst
{
    Texture::Texture(const std::string& image_n, const std::string& inter, const std::string &decal, const std::string& app)
            : image_name(image_n)
            , interpolation(inter)
            , decal_mode(decal)
            , appearance(app)
    {
        const char* image = image_n.c_str();
        read_jpeg_header(image, width, height);
        jpegImage = new unsigned char [width * height * 3];
        read_jpeg(image, jpegImage, width, height);
    }
}
