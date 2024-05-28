#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 norm;

out vec3 fsColor;

uniform mat4 u_mv;
uniform mat4 u_p;

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
  vec4 pos = u_mv * vec4(aPos, 1.0f);

  vec3 l = normalize(pos.xyz - lightData.position.xyz);
  vec3 r = reflect(-l, norm);  
  vec3 v = normalize(pos.xyz);

  vec3 Ia = lightData.ambientIntensity.xyz * u_ambientColor;
  vec3 Id = lightData.diffuseIntensity.xyz * u_diffuseColor * max(dot(l, norm), 0.0);
  vec3 Is = lightData.specularIntensity.xyz * u_specularColor * pow(max(dot(v, r), 0.0), u_shininess);

  fsColor = Ia + Id + Is;
  gl_Position = u_p * pos;
}