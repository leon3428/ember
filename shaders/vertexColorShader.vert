#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 vertexColor;
uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(aPos, 1.0);
    vertexColor = aCol;
}