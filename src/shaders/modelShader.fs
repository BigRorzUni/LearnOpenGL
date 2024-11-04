#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_specular1;

void main()
{    
    vec3 tex = vec3(texture(texture_specular1, TexCoords));
    FragColor = vec4(tex, 1.0);
}