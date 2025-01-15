#version 330 core

out vec4 FragColor;

uniform sampler2D frontTexture;
uniform sampler2D backTexture;

uniform vec3 colour;

void main()
{   
    FragColor = vec4(colour, 1.0);
}