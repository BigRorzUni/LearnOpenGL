#version 330 core

out vec4 fragColour;
in vec4 position;

void main()
{
    fragColour = position;
}