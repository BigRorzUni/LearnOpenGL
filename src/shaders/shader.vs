#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec2 aTexCoords;


layout (std140) uniform Matrices
{
                                // base alignment   // offset
    uniform mat4 projection;    // 16               // 0 (column 0)
                                // 16               // 16 (column 1)
                                // 16               // 32 (column 2)
                                // 16               // 64 (column 3)
    uniform mat4 view;          // 16               // 80 (column 0)
                                // 16               // 96 (column 1)
                                // 16               // 112 (column 2)
                                // 16               // 128 (column 3)
};

uniform mat4 model;

out VS_OUT
{
    vec2 TexCoords;
} vs_out;


void main()
{
    vs_out.TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0); // apply transformation to position
}