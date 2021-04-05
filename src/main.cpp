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
    SDL_GL_SetSwapInterval(1); 
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to initialize GLAD\n");
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    Renderer renderer = {};
    
    
    Triangle t0 = Triangle(V2( 0.0f,  0.0f), V2( 1.0f, 0.0f), V2(0.0f,  1.0f));
    Triangle t1 = Triangle(V2( 0.0f,  0.0f), V2(-1.0f, 0.0f), V2(0.0f, -1.0f));
    Triangle t2 = Triangle(V2(-1.0f,  1.0f), V2(-1.0f, 0.0f), V2(0.0f,  1.0f));
    Triangle t3 = Triangle(V2( 1.0f, -1.0f), V2( 1.0f, 0.0f), V2(0.0f, -1.0f));

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
        renderer.draw_triangle(t1);
        renderer.draw_triangle(t2);
        renderer.draw_triangle(t3);
        renderer.end(); 
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
