#pragma once

#include <glm/gtc/matrix_transform.hpp> //glm::vec3 and glm::mat4

/*
    Class represents cube as basic 3D primitive
*/
class Cube{

public:

    //Constr. & destr.
        Cube():m_Position(glm::vec3(0.0f)),m_Scale(glm::vec3(1.0f)),m_Rotation(glm::vec3(0.0f)) {}
        ~Cube() = default;
    
    //Utilities
        static const void* getVerticesArrayData() {return m_Vertices;}
        static const unsigned int getVerticesArraySize() {return 5 * 16 * sizeof(float);}

        static const unsigned int* getIndicatesArrayData() {return m_Indices;}
        static const unsigned int getIndicatesArraySize() {return 36 * sizeof(unsigned int);}

        inline void setPosition(glm::vec3 newPosition) { m_Position = newPosition; }
        inline void setPosition(float x, float y, float z) { m_Position = glm::vec3(x,y,z); } 
        inline glm::vec3 getPosition() const { return m_Position; }

        inline void setScale(float x, float y, float z) { m_Scale = glm::vec3(x,y,z); }
        inline glm::vec3 getScale() const { return m_Scale; }

        inline void setRotation(glm::vec3 newRotation) { m_Rotation = newRotation; }
        inline void setRotation(float x, float y, float z) { m_Rotation = glm::vec3(x,y,z); } 
        inline glm::vec3 getRotation() const { return m_Rotation; }

        glm::mat4 getModelMatrix() const;
private:

        void calculateModelMatrix(glm::mat4& model) const ;

private:

//Data
        //Declaration
        static const float m_Vertices[5 * 16];
        static const unsigned int m_Indices[36];

        //Maths data    
        glm::vec3 m_Position;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;   //save actual angle in radius

};//class Cube
