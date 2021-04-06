#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <stdint.h>
#include "image.h"

#define MAX_IMAGE_CAPACITY (1024)
struct Texture_Atlas
{
   Image image_array[MAX_IMAGE_CAPACITY];  
   uint32_t array_index = 0;

   uint32_t height = 0;
   uint32_t width = 0;

   void load_image(const char* filepath);
   Image generate();
   void free_images();
};

#endif //TEXTURE_ATLAS_H
