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
    //TODO: Add lifetime to each particle
    
    void update(float dt); 
    void draw(Renderer* renderer);
};

#endif //PARTICLE_H
