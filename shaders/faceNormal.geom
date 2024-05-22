#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform vec3 u_ambientColor;
uniform vec3 u_diffuseColor;
uniform vec3 u_specularColor;
uniform float u_shininess;
uniform mat4 u_p;

struct LightData {
  vec4 ambientIntensity;
  vec4 diffuseIntensity;
  vec4 specularIntensity;
  vec4 position;
};

layout(std140, binding = 2) uniform Lights { 
    LightData lightData;
};

out vec3 fsColor;

void main() {
  vec3 V1 = gl_in[0].gl_Position.xyz;
  vec3 V2 = gl_in[1].gl_Position.xyz;
  vec3 V3 = gl_in[2].gl_Position.xyz;

  vec3 c = (V1 + V2 + V3) / 3.0f;

  vec3 e1 = V2 - V1;
  vec3 e2 = V3 - V1;

  vec3 normal = normalize(cross(e2, e1));
  vec3 l = normalize(c - lightData.position.xyz);
  vec3 r = reflect(-l, normal);  
  vec3 v = normalize(c);

  vec3 Ia = lightData.ambientIntensity.xyz * u_ambientColor;
  vec3 Id = lightData.diffuseIntensity.xyz * u_diffuseColor * max(dot(l, normal), 0.0);
  vec3 Is = lightData.specularIntensity.xyz * u_specularColor * pow(max(dot(v, r), 0.0), u_shininess);

  for (int i = 0; i < 3; ++i) {
    gl_Position = u_p * gl_in[i].gl_Position;
    fsColor = Ia + Id + Is;
    EmitVertex();
  }
  EndPrimitive();
}