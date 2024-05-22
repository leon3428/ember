#version 440 core

in vec3 fsColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(fsColor, 1.0f);
} 