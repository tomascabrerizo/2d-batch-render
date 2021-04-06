#include "texture_atlas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void Texture_Atlas::load_image(const char* filepath)
{
    Image image = Image::load_bmp(filepath);
    height += image.height;
    if((uint32_t)image.width > width) width = image.width;
    image_array[array_index++] = image; 
}

Image Texture_Atlas::generate()
{
    Image atlas_image = {};
    atlas_image.width = width;
    atlas_image.height = height;
    atlas_image.pitch = width*4;
    //NOTE: Only work with 32bits or 4bytes images
    atlas_image.pixels = (void*)malloc(width*height*4);
    
    uint8_t* dest_line = (uint8_t*)atlas_image.pixels; 
    for(uint32_t i = 0; i < array_index; ++i)
    {
        Image image = image_array[i];
        uint8_t* src_line = (uint8_t*)image.pixels;
        for(int j = 0; j < image.height; ++j)
        {
            memcpy(dest_line, src_line, image.pitch);
            dest_line += width*4;
            src_line += image.pitch;
        }
    }
    return atlas_image;
}

void Texture_Atlas::free_images()
{
    for(uint32_t i = 0; i < array_index; ++i)
    {
        Image::free(image_array[array_index]);
    }
    array_index = 0;
}
