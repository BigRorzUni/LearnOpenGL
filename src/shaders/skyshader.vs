#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;

    mat4 viewNoTranslation = mat4(mat3(view)); // remove translation component so skybox is stationary
    vec4 pos = projection * viewNoTranslation * vec4(aPos, 1.0);
    gl_Position = pos.xyww; // sets z component to 1.0 (w/w due to perspective division) thus it is further away than everything else in the scene
}  