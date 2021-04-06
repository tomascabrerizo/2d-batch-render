#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "shapes.h"
#include "math.h"
#include "color.h"

#define MAX_RENDERER_CAPACITY (10000)
struct Renderer
{
    Triangle vertex_array[MAX_RENDERER_CAPACITY];
    Colorf color_array[MAX_RENDERER_CAPACITY*3];
    //TODO: ADD texture coordinates array
    uint32_t array_index;

    uint32_t program;
    uint32_t vertex_buffer;
    uint32_t color_buffer;

    Renderer();
    void init(int width, int height);
    void begin();
    void end();
    
    void draw_triangle(Triangle triangle, Color color);
    void draw_rect(Rect rect, Color color);
    void draw_rect(int x, int y, int width, int height, Color color);
};

uint32_t shader_create_program(const char* vert_path, const char* frag_path);

#endif //RENDERER_H
