#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec2 aTexCoords;

#define MAX_LIGHTS 3

out VS_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 TangentLightPos[MAX_LIGHTS];
  vec3 TangentLightDir[MAX_LIGHTS];
  vec3 TangentViewPos;
  vec3 TangentFragPos;
  vec4 LightSpacePos;
} vs_out;

uniform mat4 u_model;
uniform mat4 u_modelInv;

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

void main() {
  vec4 homPos = u_model * vec4(aPos, 1.0);
  vs_out.FragPos = vec3(homPos);   
  vs_out.TexCoords = aTexCoords;

  mat3 normalMatrix = transpose(mat3(u_modelInv));

  vec3 T = normalize(normalMatrix * aTangent);
  vec3 N = normalize(normalMatrix * aNormal);
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);

  mat3 TBN = transpose(mat3(T, B, N));    
  vs_out.TangentViewPos  = TBN * vec3(sceneData.viewPos);
  vs_out.TangentFragPos  = TBN * vs_out.FragPos;

  for(int i = 0; i < sceneData.lightCnt; i++){
    vs_out.TangentLightPos[i] = TBN * vec3(sceneData.lights[i].position);
    vs_out.TangentLightDir[i] = normalize(TBN * vec3(sceneData.lights[i].direction));
  }

  vs_out.LightSpacePos = sceneData.light_pv * homPos;

  gl_Position = sceneData.camera_pv * homPos;
}