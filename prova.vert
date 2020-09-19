#version 460
#extension GL_ARB_separate_shader_objects : enable

////////IN
layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec4 in_color;
//////////OUT
layout(location = 0) out vec4 color;

void main() 
{
    gl_Position = vec4(in_pos, 0.0, 1.0);
    color = in_color;
}