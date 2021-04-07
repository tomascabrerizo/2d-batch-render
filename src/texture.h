#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include "image.h"

struct Texture
{
    uint32_t id;
    int width;
    int height;
    

    static Texture load(const char* filepath); 
    static Texture load(Image image); 
};

#endif //TEXTURE_H
