#shader vertex
#version 330 core

layout (location = 0) in vec3 posCoords;
layout (location = 1) in vec2 texCoords;

out vec2 vtexCoords;

uniform mat4 u_mvp;

void main()
{
   vtexCoords = texCoords;
   gl_Position = u_mvp * vec4(posCoords.x, posCoords.y, posCoords.z, 1.0);
};

#shader fragment
#version 330 core

in vec2 vtexCoords;
out vec4 color;

uniform sampler2D u_texture;

void main()
{
   color = texture(u_texture, vtexCoords);
};