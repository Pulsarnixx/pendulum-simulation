#include "Line.hpp"

Line::Line(float x0, float y0, float z0, float x1, float y1, float z1){

   setPositions(x0, y0, z0, x1, y1, z1);

}

void Line::setPositions(float x0, float y0, float z0, float x1, float y1, float z1){


    m_Vertices[0] = x0;
    m_Vertices[1] = y0;
    m_Vertices[2] = z0;

    m_Vertices[3] = x1;
    m_Vertices[4] = y1;
    m_Vertices[5] = z1;

}