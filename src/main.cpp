#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <assert.h>

#include "renderer.h"
#include "texture_atlas.h"
#include "particle.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window =
        SDL_CreateWindow("2d_Renderer", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    (void)context;
    SDL_GL_SetSwapInterval(true); 
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to initialize GLAD\n");
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    //TODO: Maybe disable face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    //NOTE: Init Texture Atlas 
    Texture_Atlas ta = {};
    uint32_t luffy_texture = ta.load_image("./res/luffy.bmp");
    uint32_t woodbox_texture = ta.load_image("./res/woodbox.bmp");
    uint32_t heightmap_texture = ta.load_image("./res/heightmap.bmp");
    //NOTE: Not using texture at this moment
    (void)luffy_texture;
    (void)woodbox_texture;
    (void)heightmap_texture;
    //NOTE: Init Renderer
    Renderer renderer = {};
    renderer.init(WINDOW_WIDTH, WINDOW_HEIGHT, &ta);
    //NOTE: Free texture atlas images
    ta.free_images();
    
    //NOTE: Particle System test 
    const int max_particles = 10000;
    Particle particles[max_particles];
    int particle_index = 0;

    bool quit = false;
    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                {
                    quit = true;
                }break;
            }
        }


        int mouse_x, mouse_y; 
        uint32_t button_mask = SDL_GetMouseState(&mouse_x, &mouse_y);
        
        uint32_t mouse_lbutton_down = SDL_BUTTON(SDL_BUTTON_LEFT) & button_mask;
        if(mouse_lbutton_down && particle_index < max_particles)
        {
            for(int i = 0; i < 50; ++i)
            {
                Particle particle;
                particle.pos = V2(mouse_x, mouse_y);
                particle.size = V2(8, 8);
                particle.color = Color::RANDOM();
                particle.vel = rand_v2(V2(-40, -40), V2(40, 40));
                particle.life_time = rand_float(0, 3);
                particles[particle_index++] = particle;
                particle_index = particle_index%max_particles;
            } 
        }

        glClear(GL_COLOR_BUFFER_BIT);
        renderer.begin();
        
        for(int i = 0; i < max_particles; ++i)
        {
            particles[i].update(0.016f);
            particles[i].draw(&renderer);
        }

        renderer.end(); 
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
