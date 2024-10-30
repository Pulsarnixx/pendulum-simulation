#pragma once

#include <vector> //std::vector

/*
    Class represents sphere as basic 3D primitive
*/
class Sphere{

public:

    //Constr. & destr.
        Sphere() = delete;
        Sphere(float radius, unsigned int longitude, unsigned latitude);
        ~Sphere() = default;
    
    //Utilities
        const void* GetVerticesArrayData() {return m_Vertices.data();}
        const unsigned int GetVerticesArraySize() {return static_cast<unsigned int>(m_Vertices.size()) * sizeof(float);}

        const unsigned int* GetIndicatesArrayData() {return m_Indices.data();}
        const unsigned int GetIndicatesArraySize() {return static_cast<unsigned int>(m_Indices.size()) * sizeof(unsigned int);}

private:

    //Data
        std::vector<float> m_Vertices;
        std::vector<unsigned int> m_Indices;
        float m_CenterPoint[3];
};//class Sphere

