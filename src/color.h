#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

struct Color
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;

    static Color RANDOM();
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

const Color YELLOW = {255, 255, 0,   255}; 
const Color BLUE   = {0,   0,   255, 255};
const Color GREEN  = {0,   255, 0,   255};
const Color WHITE  = {255, 255, 255, 255};
const Color RED    = {255, 0,   0,   255};

#endif //COLOR_H
