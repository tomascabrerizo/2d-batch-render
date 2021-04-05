#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "shapes.h"

#define MAX_RENDERER_CAPACITY (1024)
struct Renderer
{
    Triangle buffer[MAX_RENDERER_CAPACITY];
    uint32_t buffer_index;

    uint32_t program;
    uint32_t location;
    uint32_t vertex_buffer;

    Renderer();
    void begin();
    void end();
    
    void draw_triangle(Triangle triangle);
};

uint32_t shader_create_program(const char* vert_path, const char* frag_path);

#endif //RENDERER_H
