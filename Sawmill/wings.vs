#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 vecColor;
out vec2 TexCoord;
  
uniform mat4 wings_transform;
uniform mat4 wings_view;
uniform mat4 wings_projection;

void main()
{
    gl_Position = wings_projection * wings_view * wings_transform * vec4(position, 1.0f);
	//gl_Position = wings_transform * vec4(position, 1.0f);
	//gl_Position =  vec4(position, 1.0f);
    vecColor = color;
    TexCoord = texCoord;
} 