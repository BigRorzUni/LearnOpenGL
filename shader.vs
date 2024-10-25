#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec3 aColour; // color has attribute position 1
layout (location = 2) in vec2 aTexCoord; // texture coordinates has attribute position 2

out vec3 ourColour;
out vec2 texCoord1;
out vec2 texCoord2;

uniform float offset;

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
    ourColour = aColour;
    texCoord1 = aTexCoord;
    texCoord2 = aTexCoord * 2;
}