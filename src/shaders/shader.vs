#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec3 aNormal; // normal has attribute position 1

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal; // normal vector stored in vertex buffer
out vec3 FragPos; // fragment position in world space

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // apply transformation to position

    // view space is used for consistency and because its faster to transform here than in fragment shader
    FragPos = vec3(view * model * vec4(aPos, 1.0)); // view position of fragment
    Normal = mat3(transpose(inverse(view * model))) * aNormal; // view position of normal
                                                        // http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/
}