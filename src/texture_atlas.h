#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <stdint.h>
#include "image.h"
#include "math.h"
#include "texture.h"

#define MAX_IMAGE_CAPACITY (1024)

struct Coord_Array 
{
    Rect_Coord texture[MAX_IMAGE_CAPACITY];
    uint32_t index;
};

struct Texture_Atlas
{
    Image image_array[MAX_IMAGE_CAPACITY];
    uint32_t array_index = 0;

    uint32_t height = 0;
    uint32_t width = 0;

    uint32_t load_image(const char* filepath);
    Image generate_image();
    Coord_Array generate_coords();
    void free_images();
};

#endif //TEXTURE_ATLAS_H
