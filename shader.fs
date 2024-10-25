#version 330 core

out vec4 fragColour;

in vec3 ourColour;
in vec2 texCoord1;
in vec2 texCoord2;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragColour = mix(texture(tex1, texCoord1), texture(tex2, texCoord2), 0.2) * vec4(ourColour, 1.0);
}