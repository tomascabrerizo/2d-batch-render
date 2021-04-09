#include "renderer.h"
#include "utils.h"
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

    return shader_program;
}

Renderer::Renderer()
{
    program = shader_create_program("./shaders/shader.vert", "./shaders/shader.frag");
    array_index = 0;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array), vertex_array, GL_DYNAMIC_DRAW);
    uint32_t location = glGetAttribLocation(program, "vertex");
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(location);
    
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_array), color_array, GL_DYNAMIC_DRAW);
    uint32_t color_location = glGetAttribLocation(program, "color_array");
    glVertexAttribPointer(color_location, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(color_location);
    
    glGenBuffers(1, &coord_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, coord_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coord_array), coord_array, GL_DYNAMIC_DRAW);
    uint32_t coord_location = glGetAttribLocation(program, "coord_array");
    glVertexAttribPointer(coord_location, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(coord_location);
    
}

void Renderer::init(int width, int height, Texture_Atlas* ta = 0)
{
    //TODO: make this transfomation with a mat2
    glUseProgram(program);
    uint32_t u_width = glGetUniformLocation(program, "width");
    uint32_t u_height = glGetUniformLocation(program, "height");
    glUniform1f(u_width, (float)width);
    glUniform1f(u_height, (float)height);

    if(ta) 
    {
        Image texture_atlas_image = ta->generate_image();
        texture_atlas_texture = Texture::load(texture_atlas_image);
        Image::free(texture_atlas_image);
        texture_atlas_coord = ta->generate_coords();
    }
    uint32_t texture_location = glGetUniformLocation(program, "texture_atlas");
    glUniform1i(texture_location , 0); 
}

void Renderer::begin()
{
    array_index = 0;
}

void Renderer::end()
{
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Triangle)*array_index, vertex_array);
    
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Colorf)*array_index*3, color_array);
    
    glBindBuffer(GL_ARRAY_BUFFER, coord_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Texture_Coord)*array_index, coord_array);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_atlas_texture.id);
    
    glDrawArrays(GL_TRIANGLES, 0, array_index*3); 
}

void Renderer::draw_triangle(Triangle triangle, Color color)
{
    vertex_array[array_index]= triangle;
    color_array[array_index*3+0] = to_colorf(color);
    color_array[array_index*3+1] = to_colorf(color);
    color_array[array_index*3+2] = to_colorf(color);
    coord_array[array_index] = Texture_Coord::INVALID();
    array_index++;
}


void Renderer::draw_triangle(Triangle triangle, Texture_Coord coord)
{
    vertex_array[array_index] = triangle;
    color_array[array_index*3+0] = Colorf::INVALID();
    color_array[array_index*3+1] = Colorf::INVALID();
    color_array[array_index*3+2] = Colorf::INVALID();
    coord_array[array_index] = coord;
    array_index++;
}

void Renderer::draw_rect(Rect rect, Color color)
{
    Rect_Split triangles = rect.split();
    draw_triangle(triangles.lower, color);
    draw_triangle(triangles.upper, color);
}

void Renderer::draw_rect(int x, int y, int width, int height, Color color)
{
    Rect rect = {{(float)x, (float)y}, {(float)width, (float)height}};
    draw_rect(rect, color);
}


void Renderer::draw_rect(int x, int y, int width, int height, uint32_t texture)
{
    Rect rect = {{(float)x, (float)y}, {(float)width, (float)height}};
    Rect_Split triangles = rect.split();
    draw_triangle(triangles.lower, texture_atlas_coord.texture[texture].lower_coords);
    draw_triangle(triangles.upper, texture_atlas_coord.texture[texture].upper_coords);
}
