#include "Circle.hpp"

#include <cmath>

#undef DEBUG
#ifdef DEBUG
    #include "../../../core/log/log.hpp"
    static std::string message;
#endif

Circle::Circle(float cx, float cy, float radius, int segments)
:m_Position(glm::vec3(cx, cy, 0.0f)), m_Translation(glm::vec3(0.0f)),m_Scale(glm::vec3(1.0f))
{


    generatePoints(cx,cy,radius, segments);

}

glm::mat4 Circle::getModelMatrix() const{

    glm::mat4 model = glm::mat4(1.0f);

    calculateModelMatrix(model);

    return model;

}

void Circle::calculateModelMatrix(glm::mat4& model) const {


    glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
    glm::mat4 rotation = glm::mat4(1.0f);
    model  = trans * rotation * scale;
}

void Circle::generatePoints(float cx, float cy, float radius, int segments){

    #ifdef DEBUG
            message = "[CIRCLE] Center point: " + std::to_string(m_Position.x) + " " + 
                                    std::to_string(m_Position.y) + " " + std::to_string(m_Position.z);
            PX_CORE_TRACE(message);
    #endif

    m_Position = glm::vec3(cx,cy,0.0f);

    m_Vertices.clear();

    for (int i = 0; i <= segments; ++i) {

        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = radius * cosf(theta) + cx;
        float y = radius * sinf(theta) + cy;
        float z = 0.0f;

        m_Vertices.push_back(x);
        m_Vertices.push_back(y);
        m_Vertices.push_back(z);

}

}