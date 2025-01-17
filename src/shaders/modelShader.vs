#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT
{
    out vec2 texcoords;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    vs_out.texcoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}