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
    
    printf("SHADER: VERTEX(%s) FRAGMENT(%s) Loaded\n", vert_path, frag_path);

    return shader_program;
}


Renderer::Renderer()
{
    program = shader_create_program("./shaders/shader.vert", "./shaders/shader.frag");
    buffer_index = 0;
    
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
}

void Renderer::end()
{
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Triangle)*buffer_index, buffer);
    glDrawArrays(GL_TRIANGLES, 0, buffer_index*3); 
}

void Renderer::draw_triangle(Triangle triangle)
{
    buffer[buffer_index]= triangle;
    buffer_index++;
}