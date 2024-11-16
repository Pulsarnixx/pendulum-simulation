#include "Circle.hpp"

#include <cmath>
#include <iostream>

#undef DEBUG
#ifdef DEBUG
    #include "../../../core/log/log.hpp"
    static std::string message;
#endif

Circle::Circle(float x0, float y0, float radius, int segments)
:m_Center(glm::vec3(x0, y0, 0.0f)), m_Radius(radius), m_Segments(segments)
{
    generatePoints(x0,y0,radius, segments);
}


void Circle::generatePoints(float x0, float y0, float radius, int segments){

    #ifdef DEBUG
            message = "[CIRCLE] Center point: " + std::to_string(m_Position.x) + " " + 
                                    std::to_string(m_Position.y) + " " + std::to_string(m_Position.z);
            PX_CORE_TRACE(message);
    #endif
    
    m_Vertices.clear();

    m_Center.x = x0;
    m_Center.y = y0;
    m_Center.z = 0.0f;

    for (int i = 0; i <= segments; ++i) {

        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = radius * cosf(theta) + x0;
        float y = radius * sinf(theta) + y0;
        float z = 0.0f;

        m_Vertices.push_back(x);
        m_Vertices.push_back(y);
        m_Vertices.push_back(z);

        std::cout << "Point: x = " << m_Vertices[i] << ", y = " << m_Vertices[i + 1] << std::endl;

    }

}

void Circle::updatePoints(float x0, float y0){

/*
    TO DO

*/

}