#pragma once

/*
    Class represents cube as basic 3D primitive
*/
class Cube{

public:

    //Constr. & destr.
        Cube() = default;
        ~Cube(){};
    
    //Utilities
        static const void* GetVerticesArrayData() {return m_Vertices;}
        static const unsigned int GetVerticesArraySize() {return 3 * 8 * sizeof(float);}

        static const unsigned int* GetIndicatesArrayData() {return m_Indices;}
        static const unsigned int GetIndicatesArraySize() {return 36 * sizeof(unsigned int);}

private:

//Data
        //Declaration
        static const float m_Vertices[3 * 8];
        static const unsigned int m_Indices[36];


//TODO: position, size

};//class Cube


//Definition static fields
const float Cube::m_Vertices[3 * 8] = {

     //position        
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f
};

const unsigned int Cube::m_Indices[36] = {
    
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,
    
    0, 3, 7,
    7, 4, 0,
    
    1, 5, 6,
    6, 2, 1,
    
    0, 1, 5,
    5, 4, 0,
    
    3, 2, 6,
    6, 7, 3
};