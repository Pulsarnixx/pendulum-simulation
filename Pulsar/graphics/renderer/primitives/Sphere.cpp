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


 //Verticies
 unsigned int points = 0;
 for (unsigned int i = 0; i <= latitude; ++i) {
    float alpha = -M_PI / 2 + i * (M_PI / latitude);
    for (unsigned int j = 0; j < longitude; ++j) {
        float beta = j * (2 * M_PI / longitude);

        float x = radius * cos(alpha) * cos(beta);
        float y = radius * cos(alpha) * sin(beta);
        float z = radius * sin(alpha);

        points+=3;

        m_Vertices.emplace_back(x);
        m_Vertices.emplace_back(y);
        m_Vertices.emplace_back(z);
    }
 }

 std::string s = "LICZBA PUNKTOW: " + std::to_string(points) + " DŁUGOSC VERTICES " + std::to_string(m_Vertices.size());
 PX_CORE_INFO(s);

}