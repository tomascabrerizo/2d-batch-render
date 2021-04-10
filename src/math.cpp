#include "math.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

float float_to_rad(float angle)
{
    return angle = angle * PI / 180;
}

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

V2 v2_rotate(V2 v, float angle)
{
    float r_angle = float_to_rad(angle);
    V2 result = {};
    result.x = cosf(r_angle)*v.x - sinf(r_angle)*v.y;
    result.y = sinf(r_angle)*v.x + cosf(r_angle)*v.y;
    return result;
}

M2 m2_ortho(float left, float rigth, float top, float bottom)
{
    //NOTE: This m2_ortho do not translate, just scale
    M2 result = {};
    result.m[0] = 2 / (rigth - left);
    result.m[1] = 0;
    result.m[2] = 0;
    result.m[3] = 2 / (top - bottom);
    return result;
}

M2 m2_identity()
{
    M2 result = {};
    result.m[0] = 1;
    result.m[1] = 0;
    result.m[2] = 0;
    result.m[3] = 1;
    return result;

}

V2 operator*(V2 v, M2 m)
{
    return V2(v.x*m.m[0]+v.y*m.m[2], v.x*m.m[1]+v.y*m.m[3]);
}
