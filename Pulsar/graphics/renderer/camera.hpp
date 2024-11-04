#pragma once

#include "glm/glm.hpp"

struct Camera{

    glm::vec3 s_position = glm::vec3(0.0f,0.0f,3.0f);
    glm::vec3 s_front = glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 s_up = glm::vec3(0.0f,1.0f,0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;

};