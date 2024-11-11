#pragma once

/*
    Class represents square as basic 2D primitive
*/
class Square{

public:

    //Constr. & destr.
        Square() = default;
        ~Square() = default;
    
    //Utilities
        static const void* GetVerticesArrayData() {return m_Vertices;}
        static const unsigned int GetVerticesArraySize() {return 4 * 3 * sizeof(float);}

        static const unsigned int* GetIndicatesArrayData() {return m_Indices;}
        static const unsigned int GetIndicatesArraySize() {return 6 * sizeof(unsigned int);}

private:

//Data
        //Declaration
        static const float m_Vertices[4 * 3];
        static const unsigned int m_Indices[6];

};//class Square


//Definition static fields
const float Square::m_Vertices[4 * 3] = {
    
    //positions
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f
};

const unsigned int Square::m_Indices[6] = {
    0, 1, 2,
    2, 3, 0
};