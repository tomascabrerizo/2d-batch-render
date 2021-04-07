#include "texture.h"
#include "image.h"
#include <assert.h>
#include <glad/glad.h>
#include <stdio.h>

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

    glGenTextures(1, &result.id);
    glBindTexture(GL_TEXTURE_2D, result.id); 
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.pixels);
    return result; 
}

Texture_Coord Texture_Coord::INVALID()
{
    return {V2(-1, -1), V2(-1, -1), V2(-1, -1)};
}
