#shader vertex
#version 330 core

layout (location = 0) in vec3 posCoords;


uniform vec4 u_color;
uniform mat4 u_mvp;

out vec4 fragColor;

void main()
{
   fragColor = u_color;
   gl_Position = u_mvp * vec4(posCoords.x, posCoords.y, posCoords.z, 1.0);
};

#shader fragment
#version 330 core

in vec4 fragColor;
out vec4 color;    

void main()
{
   color = fragColor;
};