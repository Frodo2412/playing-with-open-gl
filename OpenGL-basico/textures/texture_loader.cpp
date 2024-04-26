#include "texture_loader.h"

#include <iostream>

#include "FreeImage.h"

texture texture_loader::load_texture(const char* file_path)
{
    std::cout << "Loading texture: " << file_path << '\n';
    // LOAD IMAGE
    const FREE_IMAGE_FORMAT file_image_format = FreeImage_GetFIFFromFilename(file_path);
    FIBITMAP* bitmap = FreeImage_Load(file_image_format, file_path);
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    const unsigned int image_width = FreeImage_GetWidth(bitmap);
    const unsigned int image_height = FreeImage_GetHeight(bitmap);
    const void* image_data = FreeImage_GetBits(bitmap);

    std::cout << "- Image width: " << image_width << '\n';
    std::cout << "- Image height: " << image_height << '\n';

    // CREATE TEXTURE
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<int>(image_width),
                 static_cast<int>(image_height), 0, GL_BGR, GL_UNSIGNED_BYTE, image_data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    std::cout << "- Texture loaded: " << texture_id << '\n';

    return texture(texture_id);
}
