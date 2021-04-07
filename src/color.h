#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

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
    
    static Colorf INVALID();
};

Colorf to_colorf(Color color);

#endif //COLOR_H
