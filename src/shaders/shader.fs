#version 330 core

out vec4 FragColour;

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light 
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal; // normal of the fragment in view space
in vec3 FragPos; // position of the fragment in view space

uniform Material material;
uniform Light light;
uniform vec3 viewPos; // camera position

void main()
{
    vec3 ambient = material.ambient * light.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular = (material.specular * spec) * light.specular;

    // combine
    vec3 result = ambient + diffuse + specular;
    FragColour = vec4(result, 1.0);
}