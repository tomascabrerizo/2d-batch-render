#include "shapes.h"

Triangle::Triangle(V2 v0, V2 v1, V2 v2)
{
    vertex[0] = v0;
    vertex[1] = v1;
    vertex[2] = v2;
}
    
Rect::Rect(V2 pos, V2 dim)
{
    this->pos = pos;
    this->dim = dim;
}
    
Rect_Split Rect::split() const 
{
    Rect_Split result = {};
    float x0 = pos.x;
    float x1 = pos.x+dim.x;
    float y0 = pos.y;
    float y1 = pos.y+dim.y;
    V2 a = V2(x0, y0);
    V2 b = V2(x1, y0);
    V2 c = V2(x0, y1);
    V2 d = V2(x1, y1);
    result.lower = Triangle(a, c, d);
    result.upper = Triangle(a, d, b);
    return result; 
}
