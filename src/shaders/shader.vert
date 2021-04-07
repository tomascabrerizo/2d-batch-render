#version 120

attribute vec2 vertex;
attribute vec4 color_array;
attribute vec2 coord_array;

uniform float width;
uniform float height;

varying out vec4 color;
varying out vec2 tex_coord;

void main()
{
    color = color_array;
    tex_coord = coord_array;
    ////TODO: make this transfomation with a mat2
    float x = (vertex.x / ((width)*0.5)) - 1.0;
    float y = (vertex.y / ((-height)*0.5)) + 1.0;
    gl_Position = vec4(x, y, 0.0, 1.0);
}
