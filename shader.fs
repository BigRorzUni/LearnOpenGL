#version 330 core

out vec4 fragColour;

in vec3 ourColour;
in vec2 texCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragColour = mix(texture(tex1, texCoord), texture(tex2, texCoord), 0.2) * vec4(ourColour, 1.0);
}