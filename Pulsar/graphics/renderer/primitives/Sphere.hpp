#pragma once

#include <vector> //std::vector

/*
    Struct that represent vector in 3D space where center is in 0,0,0
*/
struct Vector3f{

public:
    Vector3f()
        :x(0.0f),y(0.0f),z(0.0f){}; 
    Vector3f(float x, float y, float z)
        :x(x),y(y),z(z){}; 
    ~Vector3f() = default;

public:
    float x;
    float y;
    float z;
};// struct Vector3f


/*
    Class represents sphere as basic 3D primitive
*/
class Sphere{

public:

    //Constr. & destr.
        Sphere() = delete;
        Sphere(Vector3f center, float radius, int sectorsNumber, int stacksNumber);
        ~Sphere() = default;
    
    //Utilities
        const void* GetVerticesArrayData() {return m_Vertices.data();}
        const unsigned int GetVerticesArraySize() {return static_cast<unsigned int>(m_Vertices.size()) * sizeof(float);}

        const unsigned int* GetIndicatesArrayData() {return m_Indices.data();}
        const unsigned int GetIndicatesArraySize() {return static_cast<unsigned int>(m_Indices.size()) * sizeof(unsigned int);}

        inline Vector3f getCenter() const { return m_Center; }
        inline float getRadius() const { return m_Radius; }
private:

    //Rendering Data
        std::vector<float> m_Vertices;
        std::vector<unsigned int> m_Indices;
    //Math data    
        Vector3f m_Center;
        float   m_Radius;
};//class Sphere

