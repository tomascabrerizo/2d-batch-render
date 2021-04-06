#version 120
attribute vec2 vertex;
attribute vec4 color_array;

uniform float width;
uniform float height;

varying out vec4 color;

void main()
{
    color = color_array;
    //TODO: make this transfomation with a mat2
    float x = (vertex.x / ((width)*0.5)) - 1.0;
    float y = (vertex.y / ((-height)*0.5)) + 1.0;
    gl_Position = vec4(x, y, 0.0, 1.0);
}
