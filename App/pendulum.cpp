#include "pendulum.hpp"

#include "Pulsar.hpp"

void InitPendulum(float x0, float y0, SinglePendulum& pendulum){
    
    pendulum.m = 25.0;
    pendulum.r = 25.0;

    pendulum.l = 500.0;
    pendulum.thetha = glm::radians(30.0);
    pendulum.thethadot = 0.0;

    pendulum.x = x0 + ( pendulum.l * sinf(pendulum.thetha));
    pendulum.y = y0 - ( pendulum.l * cosf(pendulum.thetha));

}

void InitDoublePendulum(float x0, float y0, DoublePendulum& pendulum){

    pendulum.m1 = 25.0;
    pendulum.m2 = 25.0;

    pendulum.r1 = 25.0;
    pendulum.r2 = 25.0;

    pendulum.l1 = 200.0;
    pendulum.l2 = 200.0;

    pendulum.thetha1 = glm::radians(45.0);
    pendulum.thetha2 = glm::radians(30.0);

    pendulum.thethadot1 = 0.0;
    pendulum.thethadot2 = 0.0;

    pendulum.x1 = x0 + ( pendulum.l1 * sinf(pendulum.thetha1));
    pendulum.y1 = y0 - ( pendulum.l1 * cosf(pendulum.thetha1));

    pendulum.x2 = pendulum.x1 + ( pendulum.l2 * sinf(pendulum.thetha2));
    pendulum.y2 = pendulum.y1 - ( pendulum.l2 * cosf(pendulum.thetha2));
}
