#pragma once

#include <vector> //std::vector

#include <glm/gtc/matrix_transform.hpp> //glm::vec3 and glm::mat4

/*
    Class represents circle as basic 2D primitive
*/
class Circle{

public:

    //Constr. & destr.
        Circle() = delete;
        Circle(float x0, float y0, float radius, int segments);
        ~Circle() = default;
    
    //Utilities
        void generatePoints(float x0, float y0, float radius, int segments);
        void updatePoints(float x0, float y0);
        const void* getVerticesArrayData() {return m_Vertices.data();}
        const unsigned int getVerticesArraySize() {return static_cast<unsigned int>(m_Vertices.size()) * sizeof(float);}

        inline float getRadius() const { return m_Radius; }
        inline int   getSegmentsValues() const { return m_Segments; }
        inline glm::vec3 getCenter() const { return m_Center; }

private:

    //Graphics buffer Data
        std::vector<float> m_Vertices;
        glm::vec3   m_Center;
        float       m_Radius;
        int         m_Segments;

};//class Sphere