#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <assert.h>

#include "renderer.h"

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
    
    Renderer renderer = {};
    renderer.init(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Triangle t0 = Triangle(V2( 200.0f, 200.0f), V2( 300.0f, 400.0f), V2(400.0f, 200.0f));

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
        
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.begin();
        
        renderer.draw_triangle(t0);
        renderer.draw_rect(Rect({10.0f, 10.0f}, {50.0f, 50.0f}));
        renderer.draw_rect(Rect({100.0f, 10.0f}, {50.0f, 50.0f}));

        renderer.end(); 
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
