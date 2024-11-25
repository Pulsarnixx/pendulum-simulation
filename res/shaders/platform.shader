#shader vertex
#version 330 core

layout (location = 0) in vec3 posCoords;
layout (location = 1) in vec2 texCoords;

uniform mat4 u_mvp;

void main()
{
   gl_Position = u_mvp * vec4(posCoords.x, posCoords.y, posCoords.z, 1.0);
};

#shader fragment
#version 330 core

uniform vec4 u_color;

out vec4 color;


void main()
{
   color = u_color;
};