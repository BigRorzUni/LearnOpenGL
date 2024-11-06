#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    float near = 0.1; 
    float far = 100.0; 

    float ndc = (2.0 * gl_FragCoord.z - 1.0);

    float linearDepth = (2.0 * near * far) / (far + near - ndc * (far - near));

    float depth = linearDepth / far;

    FragColor = vec4(vec3(depth), 1.0);
}