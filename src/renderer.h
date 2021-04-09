#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "shapes.h"
#include "math.h"
#include "color.h"
#include "texture_atlas.h"

#define MAX_RENDERER_CAPACITY (10000)
struct Renderer
{
    //TODO: Add more batchs to the renderer
    Triangle vertex_array[MAX_RENDERER_CAPACITY];
    Colorf color_array[MAX_RENDERER_CAPACITY*3];
    Texture_Coord coord_array[MAX_RENDERER_CAPACITY];
    uint32_t array_index;
    
    Texture texture_atlas_texture;
    Coord_Array texture_atlas_coord; 

    uint32_t program;
    uint32_t vertex_buffer;
    uint32_t color_buffer;
    uint32_t coord_buffer;

    Renderer();
    void init(int width, int height, Texture_Atlas* ta);
    void begin();
    void end();
    
    void draw_triangle(Triangle triangle, Color color);
    void draw_triangle(Triangle triangle, Texture_Coord coord);
    void draw_triangle(V2 pos, V2 size, Color color);
    void draw_rect(Rect rect, Color color);
    void draw_rect(int x, int y, int width, int height, Color color);
    void draw_rect(int x, int y, int width, int height, uint32_t texture);
};

uint32_t shader_create_program(const char* vert_path, const char* frag_path);

#endif //RENDERER_H
