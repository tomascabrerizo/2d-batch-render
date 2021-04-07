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
    //NOTE: Generate texture coordinates
    //TODO: Move this loop to the lower loop
    uint32_t current_height = 0;
    for(uint32_t i = 0; i < array_index; ++i)
    {
        Image image = image_array[i];
        Texture_Coord* coord = &coords_array[i];
        
        float right_x = (float)image.width / (float)width; 
        float upper_y = (float)current_height / (float)height;
        float bottom_y = (float)(image.height+current_height) / (float)height;
        
        coord->upper_left  = V2(0.0f, upper_y);
        coord->upper_right = V2(right_x, upper_y);
        coord->lower_left  = V2(0.0f, bottom_y);
        coord->lower_right = V2(right_x, bottom_y);
        
        //TODO: Maybe += image.height - 1; ?
        current_height += image.height;
    }

    //NOTE: Generate texture image
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
