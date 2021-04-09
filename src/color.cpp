#include "color.h"
#include "stdlib.h"

Color Color::RANDOM()
{
    return {rand()%255u, rand()%255u, rand()%255u, 255u};
}

Colorf to_colorf(Color color)
{
    return {color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f};
}

Colorf Colorf::INVALID()
{
    return {-1.0f, -1.0f, -1.0f, -1.0f};
}

