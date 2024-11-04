#include "Sphere.hpp"

#include <cmath>

#define DEBUG
#ifdef DEBUG
    #include "../../../core/log/log.hpp"
    std::string message;
#endif

/*
    Algorithm for generitic spehere is based on:
    https://pl.wikipedia.org/wiki/Sfera
    https://www.songho.ca/opengl/gl_sphere.html

    Basic formula in Euclidean space:
    (x-x_0)^2 + (y-y_0)^2 + (z-z_0)^2 = r^2, where r > 0

    Parametric equation:
    x(α, β) = x_0 + r * cosα * cosβ
    y(α, β) = y_0 + r * sinα
    z(α, β) = z_0 + r * sinα * cosβ         where:    α = [-π, π) - longitude (długość geograficzna)
                                                      β = [-π/2, π/2] - latitude (szerokość geograficzna)
    In the spherical coordinate system:
    r = const.

*/
Sphere::Sphere(Vector3f center, float radius, int sectorsNumber, int stacksNumber)
:m_Center(center){

#ifdef DEBUG
        message = "[SPHERE] Center point: " + std::to_string(m_Center.x) + " " + 
                                std::to_string(m_Center.y) + " " + std::to_string(m_Center.z);
        PX_CORE_TRACE(message);
#endif


float x,y,z;          //vertex position
float xy;             //common part for x and y = (r * cos)
float s,t;            //texture coordinates

float sectorStep = (2 * M_PI) / sectorsNumber;      //How big is step from one point to another in the row
float stackStep = M_PI / stacksNumber;              //How big is step from one point to another in the column
float sectorAngle, stackAngle;

 //Verticies
 for (int i = 0; i <= stacksNumber; ++i) {
    
    stackAngle = (M_PI / 2) - (i * stackStep);    //stackAngle = [-π/2, π/2]. Startring from π/2 to -π/2
    xy = radius * cos(stackAngle);
    z  = m_Center.z + (radius * sin(stackAngle)); //calculated here, because there is no need for sector angle

    for (int j = 0; j <= sectorsNumber; ++j) {
        sectorAngle = j * sectorStep;            //sectorAngle = [0, 2π] Startring from 0 to 2π

        //vertex positions
        x = m_Center.x + (xy * cos(sectorAngle));
        y = m_Center.y + (xy * sin(sectorAngle));

        m_Vertices.push_back(x);
        m_Vertices.push_back(y);
        m_Vertices.push_back(z);

        //texture coordinates (s, t) range between [0, 1]
        s = (float)j / sectorsNumber;
        t = (float)i / stacksNumber;
        m_Vertices.push_back(s);
        m_Vertices.push_back(t);
    }
 }


// point1--point1+1
// |  /         |
// | /          |
// point2--point2+1

int point1, point2;
for(int i = 0; i < stacksNumber; ++i)
{
    point1 = i * (sectorsNumber + 1);     // beginning of current stack
    point2 = point1 + sectorsNumber + 1;      // beginning of next stack

    for(int j = 0; j < sectorsNumber; ++j, ++point1, ++point2)
    {
        // 2 triangles per sector excluding first and last stacks
        // point1 => point2 => point1+1
      if (i < stacksNumber - 1) {
        m_Indices.push_back(point1);
        m_Indices.push_back(point2);
        m_Indices.push_back(point1 + 1);

        m_Indices.push_back(point1 + 1);
        m_Indices.push_back(point2);
        m_Indices.push_back(point2 + 1);
}
    }
}

  #ifdef DEBUG
        message = "[SPHERE] Vertex count: " + std::to_string((m_Vertices.size() / 5 ))  +
                   " Indicies count: " + std::to_string((m_Indices.size()))  ;
        PX_CORE_TRACE(message);
  #endif

}