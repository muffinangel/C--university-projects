#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vecColor;
  
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);
   //gl_Position =  vec4(position, 1.0f);
    vecColor = color;
} 