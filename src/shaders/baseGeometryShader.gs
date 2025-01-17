#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec2 texcoords;
} gs_in[];

out vec2 TexCoords;

void main() 
{    
    // process all 3 vertices of input triangle primitive
    for(int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        TexCoords = gs_in[i].texcoords;
        EmitVertex();
    }

    EndPrimitive();
}