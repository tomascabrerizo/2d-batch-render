#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include "image.h"
#include "math.h"

struct Texture_Coord 
{
    //NOTE: u and v texture coordinates between 0 and 1
    V2 v0;
    V2 v1;
    V2 v2;

    static Texture_Coord INVALID();
};

struct Rect_Coord 
{
    Texture_Coord upper_coords;
    Texture_Coord lower_coords;
};

struct Texture
{
    uint32_t id;
    uint32_t width;
    uint32_t height;

    Texture_Coord upper_coords;
    Texture_Coord lower_coords;

    static Texture load(const char* filepath); 
    static Texture load(Image image); 

};

#endif //TEXTURE_H
