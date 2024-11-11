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
        Circle(float cx, float cy, float radius, int segments);
        ~Circle() = default;
    
    //Utilities
        void generatePoints(float cx, float cy, float radius, int segments);

        const void* getVerticesArrayData() {return m_Vertices.data();}
        const unsigned int getVerticesArraySize() {return static_cast<unsigned int>(m_Vertices.size()) * sizeof(float);}

        inline float getRadius() const { return m_Radius; }

        inline void setTranslation(float x, float y, float z) { m_Translation = glm::vec3(x,y,z); } 
        inline void setPosition(glm::vec3 newPosition) { m_Position = newPosition; }
        inline void setPosition(float x, float y, float z) { m_Position = glm::vec3(x,y,z); } 
        inline glm::vec3 getPosition() const { return m_Position; }

        inline void setScale(float scale) { m_Scale = glm::vec3(1.0f * scale);  m_Radius = m_Radius * scale;}
        inline glm::vec3 getScale() const { return m_Scale; }


        glm::mat4 getModelMatrix() const;
private:
        void calculateModelMatrix(glm::mat4& model) const ;

private:

    //Graphics buffer Data
        std::vector<float> m_Vertices;
    //Maths data    
        glm::vec3 m_Position;
        glm::vec3 m_Translation;
        glm::vec3 m_Scale;
        float   m_Radius;

};//class Sphere