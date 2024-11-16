#pragma once

/*
    Class represents line as basic 2D primitive
*/
class Line{

public:

    //Constr. & destr.
        Line() = delete;
        Line(float x0, float y0, float z0, float x1, float y1, float z1);
        ~Line() = default;
    
    //Utilities
        const void* getVerticesArrayData() {return (const void*)m_Vertices;}
        const unsigned int getVerticesArraySize() {return 6 * sizeof(float);}

        void setPositions(float x0, float y0, float z0, float x1, float y1, float z1);
private:

    //Graphics buffer Data
    float m_Vertices[6];

};//class Sphere