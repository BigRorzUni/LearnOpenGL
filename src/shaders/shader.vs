#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec3 aColour; // color has attribute position 1
layout (location = 2) in vec2 aTexCoord; // texture coordinates has attribute position 2

out vec3 ourColour;
out vec2 texCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0); // apply transformation to position
    ourColour = aColour;
    texCoord = aTexCoord;
}