#version 450 core

in vec3 normal;
in vec3 viewPos;

out vec4 FragColor;

uniform vec3 u_ambientColor;
uniform vec3 u_diffuseColor;
uniform vec3 u_specularColor;
uniform float u_shininess;

struct LightData {
  vec4 ambientIntensity;
  vec4 diffuseIntensity;
  vec4 specularIntensity;
  vec4 position;
};

layout(std140, binding = 2) uniform Lights { 
  LightData lightData;
};

void main()
{
  vec3 norm = normalize(normal);

  vec3 l = normalize(viewPos - lightData.position.xyz);
  vec3 r = reflect(-l, norm);  
  vec3 v = normalize(viewPos);

  vec3 Ia = lightData.ambientIntensity.xyz * u_ambientColor;
  vec3 Id = lightData.diffuseIntensity.xyz * u_diffuseColor * max(dot(-l, norm), 0.0);
  vec3 Is = lightData.specularIntensity.xyz * u_specularColor * pow(max(dot(v, r), 0.0), u_shininess);

  FragColor = vec4(Ia + Id + Is, 1.0f);
}