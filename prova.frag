#version 460
#extension GL_ARB_separate_shader_objects : enable

///////IN
layout(location = 0) in vec4 in_color;
///////OUT
layout(location = 0) out vec4 out_color;

void main() 
{
    out_color = in_color;
}