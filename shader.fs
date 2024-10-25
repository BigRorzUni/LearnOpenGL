#version 330 core

out vec4 fragColour;

in vec3 ourColour;
in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    fragColour = texture(tex, texCoord);
}