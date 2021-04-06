#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <assert.h>

#include "renderer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const Color YELLOW = {255, 255, 0,   255}; 
const Color BLUE   = {0,   0,   255, 255};
const Color GREEN  = {0,   255, 0,   255};
const Color WHITE  = {255, 255, 255, 255};
const Color RED    = {255, 0,   0,   255};

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
    SDL_GL_SetSwapInterval(0); 
    
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
   
    //Random color array
    const int size = 10;
    const int cols = WINDOW_WIDTH / size;
    const int rows = WINDOW_HEIGHT / size;
    Color random_color_array [cols*rows];
    for(int i = 0; i < rows*cols; ++i)
    {
        random_color_array[i] = {(uint32_t)rand()%255, 
            (uint32_t)rand()%255,
            (uint32_t)rand()%255,
            (uint32_t)255
        };
    }


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
        
        for(int y = 0; y < rows; ++y)
        {
            for(int x = 0; x < cols; ++x)
            {
                renderer.draw_rect(x*size, y*size, size, size, 
                        random_color_array[y*cols+x]);
            }
        }
        
        renderer.end(); 
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
