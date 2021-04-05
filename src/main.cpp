#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <assert.h>

struct file_info
{
    char* content;
    uint32_t size;
    
};

file_info read_entire_file(const char* path)
{
    
    file_info result = {};
    FILE* file = fopen(path, "rb");
    if(!file)
    {
        printf("cannot find file (%s)\n", path);
        return result;
    }
    
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = (char*)malloc(size+1);
    fread(content, 1, size, file);
    fclose(file);
    content[size] = 0;

    result.content = content;
    result.size = size;
    return result;
}

uint32_t shader_create_program(const char* vert_path, const char* frag_path)
{
    int success;
    char infoLog[512];

    file_info vertex_shader_source = read_entire_file(vert_path);
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source.content, 0);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("ERROR(vertex_shader):%s\n", infoLog);
    };

    file_info fragment_shader_source = read_entire_file(frag_path);
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source.content, 0);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("ERROR(fragment_shader):%s\n", infoLog);
    };

    free(vertex_shader_source.content);
    free(fragment_shader_source.content);
    
    uint32_t shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("ERROR(program_shader):%s\n", infoLog);
    };

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader); 
    
    printf("SHADER: VERTEX(%s) FRAGMENT(%s) Loaded\n", vert_path, frag_path);

    return shader_program;
}

#define MAX_RENDERER_CAPACITY (1024*6)
struct Renderer
{
    float buffer[MAX_RENDERER_CAPACITY];
    uint32_t buffer_index;
    uint32_t num_of_vertices;
   
    uint32_t program;
    uint32_t location;
    uint32_t vertex_buffer;

    Renderer();
    void begin();
    void end();

    void draw_triangle(float v0, float v1, float v2, float v3, float v4, float v5);
};

Renderer::Renderer()
{
    program = shader_create_program("./shaders/shader.vert", "./shaders/shader.frag");
    buffer_index = 0;
    num_of_vertices = 0;
    
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_DYNAMIC_DRAW);
    location = glGetAttribLocation(program, "vertex");
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(location);
}

void Renderer::begin()
{
    buffer_index = 0;
    num_of_vertices = 0;
}

void Renderer::end()
{
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*buffer_index, buffer);
    glDrawArrays(GL_TRIANGLES, 0, num_of_vertices); 
}

void Renderer::draw_triangle(float v0, float v1, float v2, float v3, float v4, float v5)
{
    assert(buffer_index < MAX_RENDERER_CAPACITY);
    buffer[buffer_index++] = v0;
    buffer[buffer_index++] = v1;
    buffer[buffer_index++] = v2;
    buffer[buffer_index++] = v3;
    buffer[buffer_index++] = v4;
    buffer[buffer_index++] = v5;
    num_of_vertices += 3;
}


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window =
        SDL_CreateWindow("2d_Renderer", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1); 
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to initialize GLAD\n");
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    Renderer renderer = {};

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
        renderer.draw_triangle(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        renderer.draw_triangle(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f);
        renderer.draw_triangle(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f);
        renderer.draw_triangle(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f);
        renderer.end(); 
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
