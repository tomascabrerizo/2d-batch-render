#version 120

in vec4 color;
in vec2 tex_coord;

uniform sampler2D texture_atlas;

void main()
{
    if(color.r == -1)
    {
        gl_FragColor = texture2D(texture_atlas, tex_coord); 
    }
    else
    {
        gl_FragColor = color;
    }
}
