#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "math.h"

struct Triangle
{
    V2 vertex[3];
    Triangle() = default;
    Triangle(V2 v0, V2 v1, V2 v2);
};

struct Rect_Split
{
    Triangle upper;
    Triangle lower;
};

struct Rect 
{
    V2 pos;
    V2 dim;
    
    Rect() = default;
    Rect(V2 pos, V2 dim);
    
    Rect_Split split() const;
};

#endif //TRIANGLE_H
