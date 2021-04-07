#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <stdint.h>
#include "image.h"
#include "texture.h"
#include "math.h"

struct Texture_Coord 
{
    //NOTE: u and v texture coordinates between 0 and 1
    V2 lower_left;
    V2 lower_right;
    V2 upper_left;
    V2 upper_right;
};

#define MAX_IMAGE_CAPACITY (1024)
struct Texture_Atlas
{
    Image image_array[MAX_IMAGE_CAPACITY];
    Texture_Coord coords_array[MAX_IMAGE_CAPACITY];
    uint32_t array_index = 0;

    uint32_t height = 0;
    uint32_t width = 0;

    void load_image(const char* filepath);
    //TODO: Need to generate texture coordinates for renderer
    Image generate();
    void free_images();
};

#endif //TEXTURE_ATLAS_H
