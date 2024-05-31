#version 450 core

in vec3 normal;
in vec3 pos;
in vec4 posLightSpace;
in vec2 texCoord;

out vec4 FragColor;

uniform vec3 u_ambientColor;
uniform vec3 u_diffuseColor;
uniform vec3 u_specularColor;
uniform float u_shininess;

uniform sampler2D shadowMap;
uniform sampler2D diffuseTexture;

struct LightData {
  vec4 ambientIntensity;
  vec4 diffuseIntensity;
  vec4 specularIntensity;
  vec4 position;
};

struct SceneData {
  mat4 camera_pv;
  mat4 light_pv;
  vec4 viewPos;
  LightData lightData;
};

layout(std140, binding = 2) uniform Scene { 
  SceneData sceneData;
};

float ShadowCalculation(vec4 fragPosLightSpace, float NdL)
{
  float bias = max(0.05 * (1.0 - NdL), 0.005);  
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  projCoords = projCoords * 0.5 + 0.5;
  float closestDepth = texture(shadowMap, projCoords.xy).r; 
  float currentDepth = projCoords.z;
  float shadow = currentDepth - bias > closestDepth && projCoords.x >= 0.0f && projCoords.x <= 1.0f && projCoords.y >= 0.0f && projCoords.y <= 1.0f && currentDepth < 1.0f  ? 1.0 : 0.0;

  return shadow;
}

void main()
{
  vec3 norm = normalize(normal);

  vec3 lightDir = normalize(pos - sceneData.lightData.position.xyz);
  vec3 reflectDir = reflect(lightDir, norm);  
  vec3 viewDir = normalize(sceneData.viewPos.xyz - pos);

  vec3 texColor = texture(diffuseTexture, texCoord).xyz;
  
  float NdL = dot(-lightDir, norm);
  vec3 Ia = sceneData.lightData.ambientIntensity.xyz * u_ambientColor * texColor;
  vec3 Id = sceneData.lightData.diffuseIntensity.xyz * u_diffuseColor * texColor * max(NdL, 0.0);
  vec3 Is = sceneData.lightData.specularIntensity.xyz * u_specularColor * pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);

  float shadow = ShadowCalculation(posLightSpace, NdL);

  FragColor = vec4(Ia + (1.0 - shadow) * (Id + Is), 1.0f);
  // FragColor = vec4(shadow, 0.0f, 0.0f, 1.0f);
}