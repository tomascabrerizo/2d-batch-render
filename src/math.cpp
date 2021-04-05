#include "math.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

float float_inverse(float num)
{
    return 1.0f / num;
}

int rand_int(int min, int max)
{
    int shift =  max - min;
    int r = rand()%shift;
    return min + r; 
}

float rand_float(float min, float max)
{
    float num = (float)rand()/(float)RAND_MAX;
    num = num * (max - min) + min; 
    return num;
}

V2 rand_v2(V2 min_velocity, V2 max_velocity)
{
    return V2(
            rand_float(min_velocity.x, max_velocity.x),
            rand_float(min_velocity.y, max_velocity.y));
}

V2 operator+(V2 v0, V2 v1)
{
    return V2(v0.x+v1.x, v0.y+v1.y);
}

void operator+=(V2& v0, V2 v1)
{
    v0 = v0 + v1;
}

V2 operator-(V2 v0, V2 v1)
{
    return V2(v0.x-v1.x, v0.y-v1.y);
}

void operator-=(V2& v0, V2 v1)
{
    v0 = v0 - v1;
}

V2 operator*(V2 v, float s)
{
    return V2(v.x*s, v.y*s);
}

V2 operator*(float s, V2 v)
{
    return V2(v.x*s, v.y*s);
}

V2 operator*(V2 v0, V2 v1)
{
    return V2(v0.x*v1.x, v0.y*v1.y);
}

void operator*=(V2& v, float s)
{
    v = v * s;
}

float v2_dot(V2 v0, V2 v1)
{
    return v0.x*v1.x + v0.y*v1.y;
}

V2 v2_perp(V2 v)
{
    return V2(-v.y, v.x);
}

float v2_length_sqrt(V2 v)
{
    return v2_dot(v, v);
}

float v2_length(V2 v)
{
    return sqrtf(v2_length_sqrt(v));
}

V2 v2_normailize(V2 v)
{
    float l = v2_length(v);
    return V2(v.x/l, v.y/l);
}