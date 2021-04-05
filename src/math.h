#ifndef MATH_H
#define MATH_H

struct V2 
{
    float x;
    float y;

    V2(): x(0), y(0) {}
    V2(float x, float y): x(x), y(y) {}
};

float float_inverse(float num);
int rand_int(int min, int max);
float rand_float(float min, float max);
V2 rand_v2(V2 min_velocity, V2 max_velocity);

V2 operator+(V2 v0, V2 v1);
void operator+=(V2& v0, V2 v1);
V2 operator-(V2 v0, V2 v1);
void operator-=(V2& v0, V2 v1);
V2 operator*(V2 v, float s);
V2 operator*(float s, V2 v);
V2 operator*(V2 v0, V2 v1);
void operator*=(V2& v, float s);


float v2_dot(V2 v0, V2 v1);
V2 v2_perp(V2 v);
float v2_length_sqrt(V2 v);
float v2_length(V2 v);
V2 v2_normailize(V2 v);

#endif //MATH_H
