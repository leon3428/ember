#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;


void main() {
  vec2 V1 = gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w;
  vec2 V2 = gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w;
  vec2 V3 = gl_in[2].gl_Position.xy / gl_in[2].gl_Position.w;

  float area = (V2.x - V1.x) * (V3.y - V1.y) - (V2.y - V1.y) * (V3.x - V1.x);
  
  if (area > 0.0) {
    for (int i = 0; i < 3; ++i) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
  }
}