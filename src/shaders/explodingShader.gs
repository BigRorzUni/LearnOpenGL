#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;



void main() {    
    build_house(gl_in[0].gl_Position);
}