#pragma once

#include <vector> //std::vector

#include <glm/gtc/matrix_transform.hpp> //glm::vec3 and glm::mat4

/*
    Class represents sphere as basic 3D primitive
*/
class Sphere{

public:

    //Constr. & destr.
        Sphere() = delete;
        Sphere(float radius, int sectorsNumber, int stacksNumber);
        ~Sphere() = default;
    
    //Utilities
        const void* getVerticesArrayData() {return m_Vertices.data();}
        const unsigned int getVerticesArraySize() {return static_cast<unsigned int>(m_Vertices.size()) * sizeof(float);}

        const unsigned int* getIndicatesArrayData() {return m_Indices.data();}
        const unsigned int getIndicatesArraySize() {return static_cast<unsigned int>(m_Indices.size()) * sizeof(unsigned int);}
        
        inline float getRadius() const { return m_Radius; }

        inline void setPosition(glm::vec3 newPosition) { m_Position = newPosition; }
        inline void setPosition(float x, float y, float z) { m_Position = glm::vec3(x,y,z); } 
        inline glm::vec3 getPosition() const { return m_Position; }

        inline void setScale(float scale) { m_Scale = glm::vec3(1.0f * scale);  m_Radius = m_Radius * scale;}
        inline glm::vec3 getScale() const { return m_Scale; }

        inline void setRotation(glm::vec3 newRotation) { m_Rotation = newRotation; }
        inline void setRotation(float x, float y, float z) { m_Rotation = glm::vec3(x,y,z); } 
        inline glm::vec3 getRotation() const { return m_Rotation; }

        glm::mat4 getModelMatrix() const;
private:
        void calculateModelMatrix(glm::mat4& model) const ;

private:

    //Graphics buffer Data
        std::vector<float> m_Vertices;
        std::vector<unsigned int> m_Indices;
    //Maths data    
        glm::vec3 m_Position;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;   //save actual angle in radius
        float   m_Radius;

};//class Sphere

