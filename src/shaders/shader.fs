#version 330 core

out vec4 FragColour;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct Light 
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal; // normal of the fragment in view space
in vec3 FragPos; // position of the fragment in view space
in vec2 TexCoords;

uniform Material material;
uniform Light light;
uniform vec3 viewPos; // camera position

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
    // combine
    FragColour = vec4(ambient + diffuse + specular, 1.0);
}