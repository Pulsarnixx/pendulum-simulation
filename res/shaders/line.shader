#shader vertex
#version 330 core

layout (location = 0) in vec3 posCoords;

uniform mat4 u_mvp;

void main()
{
   gl_Position = u_mvp * vec4(posCoords.x, posCoords.y, posCoords.z, 1.0);
};

#shader fragment
#version 330 core

out vec4 color;


void main()
{
   color = vec4(0.0, 0.0, 0.0, 1.0);
};