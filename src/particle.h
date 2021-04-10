#ifndef PARTICLE_H
#define PARTICLE_H

#include "math.h"
#include "color.h"
#include "renderer.h"

struct Particle
{
    V2 pos;
    V2 vel;
    V2 size;
    Color color; 
    float angle;
    
    float life_time;
    
    void update(float dt); 
    void draw(Renderer* renderer);

};

#endif //PARTICLE_H
