#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

uniform mat4 u_p;

void main() {
  vec3 V1 = gl_in[0].gl_Position.xyz;
  vec3 V2 = gl_in[1].gl_Position.xyz;
  vec3 V3 = gl_in[2].gl_Position.xyz;

  vec3 e1 = V2 - V1;
  vec3 e2 = V3 - V1;

  vec3 normal = cross(e2, e1);

  if ( dot(V1, normal) > 0) {
    for (int i = 0; i < 3; ++i) {
      gl_Position = u_p * gl_in[i].gl_Position;
      EmitVertex();
    }
    gl_Position = u_p * gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
  }
}