#shader vertex
#version 330 core


uniform mat4 u_view;
uniform mat4 u_proj;

const vec3 position[4] = vec3[4](
   vec3(-1.0, 0.0, -1.0),
   vec3(1.0, 0.0,  -1.0),
   vec3(1.0,  0.0, 1.0),
   vec3(-1.0,  0.0, 1.0)
);

const int indicies[6] = int[6](
   0, 1, 2,
   2, 3, 0
);


mat4 createScaleMatrix(float scale) {
    return mat4(
        scale, 0.0,   0.0, 0.0,
        0.0,  scale,  0.0, 0.0,
        0.0,  0.0,    scale, 0.0,
        0.0,  0.0,    0.0,  1.0
    );
}

void main()
{
   mat4 scaleMat = createScaleMatrix(5.0);
   int Index = indicies[gl_VertexID];
   vec4 vPos = vec4(position[Index], 1.0);
   gl_Position = u_proj * u_view * scaleMat * vPos;
};

#shader fragment
#version 330 core

out vec4 color;

void main()
{

   color = vec4(0.827, 0.827, 0.827, 1.0);
};