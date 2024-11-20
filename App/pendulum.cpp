#include "pendulum.hpp"

#include <iostream>
#include "Pulsar.hpp"

//Physics const.
static const double g = 9.81;
static const double dt = 0.016;

SinglePendulum::SinglePendulum(float x0, float y0, double m, double l, double init_theta, double init_thetadot)
:m(m), l(l), theta(glm::radians(init_theta)), thetadot(init_thetadot), x0(x0), y0(y0)
{
    //Calculate initial cartesian coordinates based on polar coordinates values
    x = x0 + ( l * sin(theta));
    y = y0 - ( l * cos(theta));
}

void SinglePendulum::displayParameters(){

    std::cout << "Single Pendulum parameters: \n";

}


DoublePendulum::DoublePendulum( float x0, float y0, double m1, double m2, double l1, double l2, double init_theta1,double init_theta2,double init_thetadot1, double init_thetadot2)
:m1(m1), m2(m2), l1(l1), l2(l2),theta1(glm::radians(init_theta1)), theta2(glm::radians(init_theta2)), thetadot1(init_thetadot1), thetadot2(init_thetadot2), x0(x0), y0(y0)
{

    //Calculate initial cartesian coordinates based on polar coordinates values
    x1 = x0 + ( l1 * sin(theta1));
    y1 = y0 - ( l1 * cos(theta1));

    x2 = x0 + (  l1 * sin(theta1)) + (  l2 * sin(theta2));
    y2 = y0 - (  l1 * cos(theta1)) - (  l2 * cos(theta2));

}

void DoublePendulum::displayParameters(){

    std::cout << "Double Pendulum parameters: \n";

}

void ResetPendulum(SinglePendulum& pendulum){}

void ResetPendulum(DoublePendulum& pendulum){}

void SimulatePendulumApprox(SinglePendulum& pendulum){

    //Calculate properties in polar coordinates
    double thetaddot = -(g / pendulum.l) * pendulum.theta;
    pendulum.thetadot += (thetaddot * dt);    
    pendulum.theta += (pendulum.thetadot * dt);

    //Update cartesian coordinates based on polar coordinates values
    pendulum.x = pendulum.x0 + ( pendulum.l * sin(pendulum.theta));
    pendulum.y = pendulum.y0 - ( pendulum.l * cos(pendulum.theta));

}

void SimulatePendulumEuler(SinglePendulum& pendulum){

    //Calculate properties in polar coordinates
    double thetaddot = -(g / pendulum.l) * sin(pendulum.theta);
    pendulum.thetadot += (thetaddot * dt);    
    pendulum.theta += (pendulum.thetadot * dt);

    //Update cartesian coordinates based on polar coordinates values
    pendulum.x = pendulum.x0 + ( pendulum.l * sin(pendulum.theta));
    pendulum.y = pendulum.y0 - ( pendulum.l * cos(pendulum.theta));
}

void SimulatePendulumRK2(SinglePendulum& pendulum){

    //Calcualte k1,k2 parameters for theta and thetadot
    double k1_theta = dt * pendulum.thetadot;
    double k1_thetadot = dt * (-(g / pendulum.l) * sin(pendulum.theta));

    double k2_theta = dt * ( pendulum.thetadot + (0.5 * k1_thetadot) );
    double k2_thetadot = dt * ( -(g / pendulum.l) * sin(pendulum.theta + 0.5 * k1_theta) );

    pendulum.thetadot = pendulum.thetadot + k2_thetadot;
    pendulum.theta = pendulum.theta + k2_theta;

    //Update cartesian coordinates based on polar coordinates values
    pendulum.x = pendulum.x0 + ( pendulum.l * sin(pendulum.theta));
    pendulum.y = pendulum.y0 - ( pendulum.l * cos(pendulum.theta));


}

void SimulatePendulumRK4(SinglePendulum& pendulum){

    //Calcualte k1,k2 parameters for theta and thetadot
    double k1_theta = dt * pendulum.thetadot;
    double k1_thetadot = dt * (-(g / pendulum.l) * sin(pendulum.theta));

    double k2_theta = dt * ( pendulum.thetadot + (0.5 * k1_thetadot) );
    double k2_thetadot = dt * ( -(g / pendulum.l) * sin(pendulum.theta + 0.5 * k1_theta) );

    double k3_theta = dt * ( pendulum.thetadot + (0.5 * k2_thetadot) );
    double k3_thetadot = dt * ( -(g / pendulum.l) * sin(pendulum.theta + 0.5 * k2_theta) );

    double k4_theta = dt * ( pendulum.thetadot + k3_thetadot);
    double k4_thetadot = dt * ( -(g / pendulum.l) * sin(pendulum.theta + k3_theta) );

    pendulum.thetadot = pendulum.thetadot + ((k1_thetadot + 2 * k2_thetadot + 2 * k3_thetadot + k4_thetadot) / 6 );
    pendulum.theta = pendulum.theta + ((k1_theta + 2 * k2_theta + 2 * k3_theta + k4_theta) / 6 );

    //Update cartesian coordinates based on polar coordinates values
    pendulum.x = pendulum.x0 + ( pendulum.l * sin(pendulum.theta));
    pendulum.y = pendulum.y0 - ( pendulum.l * cos(pendulum.theta));


}

void SimulatePendulumEuler(DoublePendulum& pendulum){

    //Calculation helpful expressions 
    double a = ( -1 * (pendulum.m1 + pendulum.m2) * g * sin(pendulum.theta1) ) -( pendulum.m2 * pendulum.l2 * pendulum.thetadot2 * pendulum.thetadot2 * sin(pendulum.theta1 - pendulum.theta2) );
    double b = (pendulum.m1 + pendulum.m2) * pendulum.l1;
    double c = pendulum.m2 * pendulum.l2 * cos(pendulum.theta1 - pendulum.theta2);
    double d = -1 * g * sin(pendulum.theta2) + pow(pendulum.thetadot1,2) * pendulum.l1 * sin(pendulum.theta1 - pendulum.theta2);
    double e = pendulum.l1 * cos(pendulum.theta1 - pendulum.theta2);
    double f = pendulum.l2;

    //Calculate properties in polar coordinates for both masses
    double thetaddot2 = (d - (e * a)) / (f - (e*c));
    double thetaddot1 = (a - (c * thetaddot2)) / b;

    pendulum.thetadot2 = pendulum.thetadot2 + dt * thetaddot2;
    pendulum.theta2 = pendulum.theta2 + dt * pendulum.thetadot2;

    pendulum.thetadot1 = pendulum.thetadot1 + dt * thetaddot1;
    pendulum.theta1 = pendulum.theta1 + dt * pendulum.thetadot1;

    //Update cartesian coordinates based on polar coordinates values for both masses
    pendulum.x1 = pendulum.x0 + ( pendulum.l1 * sin(pendulum.theta1)); 
    pendulum.y1 = pendulum.y0 - ( pendulum.l1 * cos(pendulum.theta1));

    pendulum.x2 = pendulum.x0 + ( pendulum.l1 * sin(pendulum.theta1)) + ( pendulum.l2 * sin(pendulum.theta2));
    pendulum.y2 = pendulum.y0 - ( pendulum.l1 * cos(pendulum.theta1)) - ( pendulum.l2 * cos(pendulum.theta2));
}