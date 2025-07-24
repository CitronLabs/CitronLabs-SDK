#version 460 core 

layout (location = 0) in vec4 i_pos;
layout(location = 1) in vec4 i_color;

out vec4 vertexColor;


void main() { 
    gl_Position = i_pos;
    vertexColor = i_color;
}
