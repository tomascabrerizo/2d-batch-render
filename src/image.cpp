#include "image.h"
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

Image Image::load_bmp(const char* filepath)
{
    SDL_Surface* sdl_image = SDL_LoadBMP(filepath);
    Image result = {};
    
    result.width = sdl_image->w;
    result.height = sdl_image->h;
    result.pitch = sdl_image->pitch;
    
    //Maybe only support 32bits images 
    const size_t image_size = sdl_image->pitch*sdl_image->h;
    result.pixels = (void*)std::malloc(image_size);
    
    memcpy(result.pixels, sdl_image->pixels, image_size);
    
    SDL_FreeSurface(sdl_image);
    
    return result;
}


void Image::save_bmp(Image image, const char* filepath)
{
    SDL_Surface* sdl_image = SDL_CreateRGBSurfaceFrom(
            image.pixels,
            image.width, image.height,
            32, image.pitch,
            0x00FF0000,
            0x0000FF00,
            0x000000FF, 
            0xFF000000
    );
    SDL_SaveBMP(sdl_image, filepath);
    SDL_FreeSurface(sdl_image);
}

void Image::free(Image image)
{
    std::free(image.pixels);
}
