#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec2 aTexCoords; // texture coordinates has attribute position 1

out vec2 TexCoords; // texture coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    TexCoords = aTexCoords; // pass texture coordinates to fragment shader

    gl_Position = projection * view * model * vec4(aPos, 1.0); // apply transformation to position
}