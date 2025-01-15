#version 330 core

out vec4 FragColor;

uniform sampler2D frontTexture;
uniform sampler2D backTexture;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

void main()
{   
    if(gl_FrontFacing)
        FragColor = texture(frontTexture, fs_in.TexCoords);
    else
        FragColor = texture(backTexture, fs_in.TexCoords);
}