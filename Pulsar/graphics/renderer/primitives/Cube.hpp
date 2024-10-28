#pragma once

/*
    Class represents cube as basic 3D primitive
*/
class Cube{

public:

    //Constr. & destr.
        Cube() = default;
        ~Cube() = default;
    
    //Utilities
        static const void* GetVerticesArrayData() {return m_Vertices;}
        static const unsigned int GetVerticesArraySize() {return 5 * 16 * sizeof(float);}

        static const unsigned int* GetIndicatesArrayData() {return m_Indices;}
        static const unsigned int GetIndicatesArraySize() {return 36 * sizeof(unsigned int);}

private:

//Data
        //Declaration
        static const float m_Vertices[5 * 16];
        static const unsigned int m_Indices[36];


//TODO: position, size

};//class Cube


//Definition static fields
const float Cube::m_Vertices[5 * 16] = {

     //position             //texture
    // -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  
    //  0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  
    //  0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  
    // -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  

    // -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    //  0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
    //  0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    // -0.5f,  0.5f,  0.5f,   0.0f, 1.0f 

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
    
    // 0, 1, 2,
    // 2, 3, 0,

    // 4, 5, 6,
    // 6, 7, 4,
    
    // 0, 3, 7,
    // 7, 4, 0,
    
    // 1, 5, 6,
    // 6, 2, 1,
    
    // 0, 1, 5,
    // 5, 4, 0,
    
    // 3, 2, 6,
    // 6, 7, 3

        
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