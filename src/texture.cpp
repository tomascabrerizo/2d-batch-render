#include "texture.h"
#include "image.h"
#include <assert.h>
#include <glad/glad.h>

Texture Texture::load(const char* filepath)
{
    Image image = Image::load_bmp(filepath);
    Texture result = load(image);
    Image::free(image);
    return result;
}

Texture Texture::load(Image image)
{
    assert(image.pixels);
    Texture result = {};
    result.width = image.width;
    result.height = image.height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (char*)image.pixels);

    return result; 
} 
