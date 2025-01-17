#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec2 texcoords;
} gs_in[];

uniform float Time;

out vec2 TexCoords;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
    return normalize(cross(a,b));
}

vec4 Explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(Time) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
}

void main() 
{    
    vec3 Normal = GetNormal();
    // process all 3 vertices of input triangle primitive
    for(int i = 0; i < 3; i++)
    {
        gl_Position = Explode(gl_in[i].gl_Position, Normal);
        TexCoords = gs_in[i].texcoords;
        EmitVertex();
    }

    EndPrimitive();
}