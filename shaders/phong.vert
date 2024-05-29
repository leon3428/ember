#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 norm;

out vec3 normal;
out vec3 viewPos;

uniform mat4 u_mv;
uniform mat4 u_p;
uniform mat3 u_normMat;

void main()
{
  normal = u_normMat * norm;

  vec4 pos = u_mv * vec4(aPos, 1.0f);
  viewPos = pos.xyz;
  gl_Position = u_p * pos;
}