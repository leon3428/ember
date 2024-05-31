#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_model;

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
    gl_Position = sceneData.light_pv * u_model * vec4(aPos, 1.0);
}