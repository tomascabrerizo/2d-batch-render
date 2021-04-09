#include "particle.h"
#include "stdio.h"

void Particle::update(float dt)
{
    if(life_time > 0.0f)
    {
        pos += vel * dt;
        life_time -= dt;
    }
}

void Particle::draw(Renderer* renderer)
{
    if(life_time > 0.0f)
        renderer->draw_rect(pos.x, pos.y, size.x, size.y, color);
}

