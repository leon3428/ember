#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec3 pos;
out vec4 posLightSpace;
out vec2 texCoord;

uniform mat4 u_model;
uniform mat4 u_modelInv;

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

void main()
{
  normal = transpose(mat3(u_modelInv)) * aNorm;

  vec4 posHom = u_model * vec4(aPos, 1.0f);
  pos = posHom.xyz;
  posLightSpace = sceneData.light_pv * posHom;
  texCoord = aTexCoord;
  gl_Position = sceneData.camera_pv * posHom;
}