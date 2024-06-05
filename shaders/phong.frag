#version 450 core

out vec4 FragColor;

uniform vec3 u_ambientColor;
uniform vec3 u_diffuseColor;
uniform vec3 u_specularColor;
uniform float u_shininess;

uniform sampler2D shadowMap;
uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;

#define MAX_LIGHTS 3

in VS_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 TangentLightPos[MAX_LIGHTS];
  vec3 TangentLightDir[MAX_LIGHTS];
  vec3 TangentViewPos;
  vec3 TangentFragPos;
  vec4 LightSpacePos;
} fs_in;

struct LightData {
  vec4 diffuseIntensity;
  vec4 specularIntensity;
  vec4 position;
  vec4 direction;
  float cosAngle;
};

struct SceneData {
  mat4 camera_pv;
  mat4 light_pv;
  vec4 viewPos;
  vec4 ambientIntensity;
  LightData lights[MAX_LIGHTS];
  int lightCnt;
};

layout(std140, binding = 2) uniform Scene { 
  SceneData sceneData;
};

float ShadowCalculation(vec4 fragPosLightSpace, float NdL) {
  float bias = max(0.05 * (1.0 - NdL), 0.005);  
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  projCoords = projCoords * 0.5 + 0.5;
  float closestDepth = texture(shadowMap, projCoords.xy).r; 
  float currentDepth = projCoords.z;
  float shadow = currentDepth - bias > closestDepth && projCoords.x >= 0.0f && projCoords.x <= 1.0f && projCoords.y >= 0.0f && projCoords.y <= 1.0f && currentDepth < 1.0f  ? 1.0 : 0.0;

  return shadow;
}

vec3 CalcSpotLight(int i, vec3 normal, vec3 viewDir, vec3 texColor) {
  vec3 lightDir = normalize(fs_in.TangentLightPos[i] - fs_in.TangentFragPos);
  float theta = dot(fs_in.TangentLightDir[i], lightDir);

  if(theta > sceneData.lights[i].cosAngle) {
    vec3 reflectDir = reflect(-lightDir, normal);
    float NdL = dot(lightDir, normal);
    
    vec3 Id = sceneData.lights[i].diffuseIntensity.xyz * u_diffuseColor * texColor * max(NdL, 0.0);
    vec3 Is = sceneData.lights[i].specularIntensity.xyz * u_specularColor * pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);

    if(i == 0) {
      float shadow = ShadowCalculation(fs_in.LightSpacePos, NdL);
      return (1.0 - shadow) * (Id + Is);
    }

    return Id + Is;
  } else {
    return vec3(0.0f);
  }
}

void main() {
  vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
  normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
  vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
  vec3 texColor = texture(diffuseTexture, fs_in.TexCoords).xyz;
  vec3 color = sceneData.ambientIntensity.xyz * u_ambientColor * texColor;

  for(int i = 0; i < sceneData.lightCnt; i++) {
    color += CalcSpotLight(i, normal, viewDir, texColor);
  }

  FragColor = vec4(color, 1.0f);
}