#include "Sphere.hpp"

#include <cmath>

#define DEBUG
#ifdef DEBUG
    #include "../../../core/log/log.hpp"
#endif

/*
    Algorithm for generitic spehere is based on:
    https://pl.wikipedia.org/wiki/Sfera

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
Sphere::Sphere(float radius, unsigned int longitude, unsigned latitude){

 //Define center point as {0,0,0}
 m_CenterPoint[0] = 0.0f; //x
 m_CenterPoint[1] = 0.0f; //y
 m_CenterPoint[2] = 0.0f; //z 

 //Verticies
 unsigned int points = 0;
 for (unsigned int i = 0; i <= latitude; ++i) {
    float alpha = -M_PI / 2 + i * (M_PI / latitude);
    for (unsigned int j = 0; j < longitude; ++j) {
        float beta = j * (2 * M_PI / longitude);

        float x = m_CenterPoint[0] + (radius * cos(alpha) * cos(beta));
        float y = m_CenterPoint[1] + (radius * cos(alpha) * sin(beta));
        float z = m_CenterPoint[2] + (radius * sin(alpha));

        points+=3;

        m_Vertices.emplace_back(x);
        m_Vertices.emplace_back(y);
        m_Vertices.emplace_back(z);
    }
 }

  #ifdef DEBUG
        std::string message = "[SPHERE] " + std::to_string((m_Vertices.size() / 3 )) + " verticies" ;
        PX_CORE_TRACE(message);
  #endif

}