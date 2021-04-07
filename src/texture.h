#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

struct Texture
{
    uint32_t id;
    int width;
    int height;
    

    static Texture load(const char* filepath); 
};

#endif //TEXTURE_H
