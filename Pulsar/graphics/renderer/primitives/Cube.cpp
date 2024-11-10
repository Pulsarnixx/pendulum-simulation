#include "Cube.hpp"

#include <cmath>


//Definition static fields
const float Cube::m_Vertices[5 * 16] = {

    //position            //texture
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,//0
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,//1
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//2
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,//3
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//4
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,//5
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,//6
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,//7
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//8
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//9
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//10
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//11
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//12
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//13       
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,//14                              
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f//15
};

const unsigned int Cube::m_Indices[36] = {
        
    0, 1, 2, //1 surface
    2, 3, 0,

    4, 5, 6, //2 ...
    6, 7, 4,

    8, 9, 10,
    10, 4, 8,

    11, 2, 12,
    12, 13, 11,

    10, 14, 5,
    5, 4, 10,

    3, 2, 11,
    11, 15, 3
};

glm::mat4 Cube::getModelMatrix() const{

    glm::mat4 model = glm::mat4(1.0f);

    calculateModelMatrix(model);

    return model;

}

void Cube::calculateModelMatrix(glm::mat4& model) const {

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),  glm::radians(m_Rotation.x), glm::vec3(1.0f,0.0f,0.0f));   //X-axis rotation
              rotation = glm::rotate(rotation,  glm::radians(m_Rotation.y), glm::vec3(0.0f,1.0f,0.0f));          //Y-axis rotation
              rotation = glm::rotate(rotation, glm::radians(m_Rotation.z), glm::vec3(0.0f,0.0f,1.0f));           //Z-axis rotation
    
    model  = trans * rotation * scale;
}