#include "particle.h"
#include "stdio.h"

void Particle::update(float dt)
{
    pos += vel * dt;
}

void Particle::draw(Renderer* renderer)
{
    renderer->draw_rect(pos.x, pos.y, size.x, size.y, color);
}

