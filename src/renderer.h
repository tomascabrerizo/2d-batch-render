#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "shapes.h"
#include "math.h"

struct Color
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
};

struct Colorf 
{
    float r;
    float g;
    float b;
    float a;

};

Colorf to_colorf(Color color);

#define MAX_RENDERER_CAPACITY (10000)
struct Renderer
{
    Triangle buffer[MAX_RENDERER_CAPACITY];
    Colorf color_array[MAX_RENDERER_CAPACITY*3];
    uint32_t buffer_index;

    uint32_t program;
    uint32_t vertex_buffer;
    uint32_t color_buffer;

    Renderer();
    void init(int width, int height);
    void begin();
    void end();
    
    void draw_triangle(Triangle triangle, Color color);
    void draw_rect(Rect rect, Color color);
};

uint32_t shader_create_program(const char* vert_path, const char* frag_path);

#endif //RENDERER_H
