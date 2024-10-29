#version 330 core

out vec4 FragColour;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightPos; // light position

in vec3 Normal; // normal of the fragment
in vec3 FragPos; // position of the fragment

void main()
{
    // ambient
    float ambientStrength = 0.1;

    vec3 ambient = ambientStrength * lightColour;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = diff * lightColour;


    vec3 result = (ambient + diffuse) * objectColour;
    FragColour = vec4(result, 1.0);
}