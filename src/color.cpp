#include "color.h"

Colorf to_colorf(Color color)
{
    return {color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f};
}

