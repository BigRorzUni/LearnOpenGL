#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in VS_OUT 
{
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.2;

uniform mat4 projection;

void GenerateLine(int index)
{
    gl_Position = projection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal

    /*
    
    // get center of the face
    vec4 faceCentre = gl_in[0].gl_Position + (gl_in[1].gl_Position / 2) + (gl_in[2].gl_Position / 2);

    // get average normal on the face
    vec3 avgNormal = (gs_in[0].normal + gs_in[1].normal + gs_in[2].normal) / 3;

    gl_Position = projection * faceCentre;
    EmitVertex();
    gl_Position = projection * (faceCentre + vec4(avgNormal, 0.0) * MAGNITUDE);
    EmitVertex();
    EndPrimitive();
    */
}