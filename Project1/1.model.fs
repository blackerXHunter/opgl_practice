#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    //sampler2D texture_emission1;
    float shininess;
};
uniform Material material;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight{
    vec3 direction;
    vec3 position;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotLight;

uniform vec3 viewPos;


void main()
{   
    vec3 result = vec3(0.0f);
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lightDir = normalize(-dirLight.direction);

    vec3 diffuseColor = vec3(texture(material.texture_diffuse1, TexCoords));
    float diff = max(dot(lightDir, normal), 0);

    vec3 specularColor = vec3(texture(material.texture_specular1, TexCoords));
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    result += diffuseColor * 0.1 * dirLight.ambient;
    result += diffuseColor * diff * dirLight.diffuse;

    result += specularColor * spec * dirLight.specular;
    
    FragColor = vec4(result, 1.0f);
    //FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
