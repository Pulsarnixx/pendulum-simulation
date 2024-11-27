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

    //Save initial values;
    this->init_theta = glm::radians(init_theta);
    this->init_thetadot = glm::radians(init_thetadot);

}

void SinglePendulum::ResetValues(){

    theta = init_theta;
    thetadot = init_thetadot;
}

void SinglePendulum::UpdateCartesianCoordinates(){

    x = x0 + ( l * sin(theta));
    y = y0 - ( l * cos(theta));
}


double SinglePendulum::getKinematicEnergy(){
     return (0.5 * m * pow(l,2) * pow(thetadot,2));
}

double SinglePendulum::getPotencialEnergy(){
     return ( m * g * l * (1 - cos(theta)));
}




DoublePendulum::DoublePendulum( float x0, float y0, double m1, double m2, double l1, double l2, double init_theta1,double init_theta2,double init_thetadot1, double init_thetadot2)
:m1(m1), m2(m2), l1(l1), l2(l2),theta1(glm::radians(init_theta1)), theta2(glm::radians(init_theta2)), thetadot1(init_thetadot1), thetadot2(init_thetadot2), x0(x0), y0(y0)
{

    //Calculate initial cartesian coordinates based on polar coordinates values
    x1 = x0 + ( l1 * sin(theta1));
    y1 = y0 - ( l1 * cos(theta1));

    x2 = x0 + (  l1 * sin(theta1)) + (  l2 * sin(theta2));
    y2 = y0 - (  l1 * cos(theta1)) - (  l2 * cos(theta2));

    //Save initial values;
    this->init_theta1 = glm::radians(init_theta1);
    this->init_thetadot1 = glm::radians(init_thetadot1);
    this->init_theta2 = glm::radians(init_theta2);
    this->init_thetadot2 = glm::radians(init_thetadot2);


}


double DoublePendulum::getKinematicEnergy(){
    return ( ( 0.5 * m1 * l1 * l1 * thetadot1 * thetadot1 ) + 
             ( 0.5 * m2 * ( (l1 * l1 * thetadot1 * thetadot1) + (l2 * l2 * thetadot2 * thetadot2) + (2 * l1 * l2 * thetadot1 * thetadot2 * cos(theta1 - theta2)) ) )
            );
}

double DoublePendulum::getPotencialEnergy(){
    return (   (-1.0 * m1 * g * l1 * cos(theta1)) - ( m2 * g * ( (l1 * cos(theta1)) + (l2 * cos(theta2)) ) )
             
             );
}

void DoublePendulum::ResetValues(){

    theta1 = init_theta1;
    thetadot1 = init_thetadot1;
    theta2 = init_theta2;
    thetadot2 = init_thetadot2;

}

void DoublePendulum::UpdateCartesianCoordinates(){

    x1 = x0 + ( l1 * sin(theta1));
    y1 = y0 - ( l1 * cos(theta1));

    x2 = x0 + (  l1 * sin(theta1)) + (  l2 * sin(theta2));
    y2 = y0 - (  l1 * cos(theta1)) - (  l2 * cos(theta2));
}


/*
===============================================================
        Single Pendulum numerical calculations
===============================================================
*/
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

void SimulatePendulumHeun(SinglePendulum& pendulum){

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

/*
===============================================================
        Double Pendulum numerical calculations
===============================================================
*/

double calculateThetaddot2(double l1, double l2, double m1, double m2, double theta1, double theta2, double thetadot1, double thetadot2){

    //helpful expressions 
    double a = ( -1 * (m1 + m2) * g * sin(theta1) ) -( m2 * l2 * thetadot2 * thetadot2 * sin(theta1 - theta2) );
    double c = m2 * l2 * cos(theta1 - theta2);
    double d = -1 * g * sin(theta2) + pow(thetadot1,2) * l1 * sin(theta1 - theta2);
    double e = l1 * cos(theta1 - theta2);
    double f = l2;


    double thetaddot2 = (d - (e * a)) / (f - (e*c));
    return thetaddot2;

}

double calculateThetaddot1(double l1, double l2, double m1, double m2, double theta1, double theta2, double thetadot2, double thetaddot2){

    //helpful expressions 
    double a = ( -1 * (m1 + m2) * g * sin(theta1) ) -( m2 * l2 * thetadot2 * thetadot2 * sin(theta1 - theta2) );
    double b = (m1 + m2) * l1;
    double c = m2 * l2 * cos(theta1 - theta2);

    
    double thetaddot1 = (a - (c * thetaddot2)) / b;
    return thetaddot1;

}

void SimulatePendulumEuler(DoublePendulum& pendulum){

    //Calculate properties in polar coordinates for both masses
    double thetaddot2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2, pendulum.theta1, pendulum.theta2,
                            pendulum.thetadot1, pendulum.thetadot2);

    double thetaddot1 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2, pendulum.theta1, pendulum.theta2,
                                            pendulum.thetadot2, thetaddot2);                        

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

void SimulatePendulumHeun(DoublePendulum& pendulum){

    //Calculate thetaddots for k1
    double thetaddot2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2, pendulum.theta1, pendulum.theta2,
                            pendulum.thetadot1, pendulum.thetadot2);

    double thetaddot1 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2, pendulum.theta1, pendulum.theta2,
                                            pendulum.thetadot2, thetaddot2);   


    //Calculate k1s
    double k1_theta2 = dt * pendulum.thetadot2;
    double k1_thetadot2 = dt * thetaddot2;
    double k1_theta1 = dt * pendulum.thetadot1;
    double k1_thetadot1 = dt * thetaddot1;

    //Calculate thetaddots for k2
    double thetaddot2_k2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                            pendulum.theta1 + 0.5 * k1_theta1, pendulum.theta2 + 0.5 * k1_theta2,
                            pendulum.thetadot1 + 0.5 * k1_thetadot1, pendulum.thetadot2  + 0.5 * k1_thetadot2);

    double thetaddot1_k2 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                                               pendulum.theta1 + 0.5 * k1_theta1, pendulum.theta2 + 0.5 * k1_theta2,
                                               pendulum.thetadot2  + 0.5 * k1_thetadot2, thetaddot2_k2);  

    //Calculate k2s
    double k2_theta2 = dt * (pendulum.thetadot2 + 0.5 * k1_thetadot2);
    double k2_thetadot2 = dt * thetaddot2_k2;
    double k2_theta1 = dt * (pendulum.thetadot1 + 0.5 * k1_thetadot1);
    double k2_thetadot1 = dt * thetaddot1_k2;


    //Update properties based on RK2                                        
    pendulum.thetadot2 = pendulum.thetadot2 + k2_thetadot2;
    pendulum.theta2 = pendulum.theta2 + k2_theta2;

    pendulum.thetadot1 = pendulum.thetadot1 + k2_thetadot1;
    pendulum.theta1 = pendulum.theta1 + k2_theta1;

    //Update cartesian coordinates based on polar coordinates values for both masses
    pendulum.x1 = pendulum.x0 + ( pendulum.l1 * sin(pendulum.theta1)); 
    pendulum.y1 = pendulum.y0 - ( pendulum.l1 * cos(pendulum.theta1));

    pendulum.x2 = pendulum.x0 + ( pendulum.l1 * sin(pendulum.theta1)) + ( pendulum.l2 * sin(pendulum.theta2));
    pendulum.y2 = pendulum.y0 - ( pendulum.l1 * cos(pendulum.theta1)) - ( pendulum.l2 * cos(pendulum.theta2));
}

void SimulatePendulumRK4(DoublePendulum& pendulum){

    //Calculate thetaddots for k1
    double thetaddot2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2, pendulum.theta1, pendulum.theta2,
                            pendulum.thetadot1, pendulum.thetadot2);

    double thetaddot1 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2, pendulum.theta1, pendulum.theta2,
                                            pendulum.thetadot2, thetaddot2);   


    //Calculate k1s
    double k1_theta2 = dt * pendulum.thetadot2;
    double k1_thetadot2 = dt * thetaddot2;
    double k1_theta1 = dt * pendulum.thetadot1;
    double k1_thetadot1 = dt * thetaddot1;

    //Calculate thetaddots for k2
    thetaddot2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                            pendulum.theta1 + 0.5 * k1_theta1, pendulum.theta2 + 0.5 * k1_theta2,
                            pendulum.thetadot1 + 0.5 * k1_thetadot1, pendulum.thetadot2  + 0.5 * k1_thetadot2);

    thetaddot1 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                                               pendulum.theta1 + 0.5 * k1_theta1, pendulum.theta2 + 0.5 * k1_theta2,
                                               pendulum.thetadot2  + 0.5 * k1_thetadot2, thetaddot2);  

    //Calculate k2s
    double k2_theta2 = dt * (pendulum.thetadot2 + 0.5 * k1_thetadot2);
    double k2_thetadot2 = dt * thetaddot2;
    double k2_theta1 = dt * (pendulum.thetadot1 + 0.5 * k1_thetadot1);
    double k2_thetadot1 = dt * thetaddot1;

    //Calculate thetaddots for k3
    thetaddot2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                            pendulum.theta1 + 0.5 * k2_theta1, pendulum.theta2 + 0.5 * k2_theta2,
                            pendulum.thetadot1 + 0.5 * k2_thetadot1, pendulum.thetadot2  + 0.5 * k2_thetadot2);

    thetaddot1 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                                               pendulum.theta1 + 0.5 * k2_theta1, pendulum.theta2 + 0.5 * k2_theta2,
                                               pendulum.thetadot2  + 0.5 * k2_thetadot2, thetaddot2); 

    double k3_theta2 = dt * (pendulum.thetadot2 + 0.5 * k2_thetadot2);
    double k3_thetadot2 = dt * thetaddot2;
    double k3_theta1 = dt * (pendulum.thetadot1 + 0.5 * k2_thetadot1);
    double k3_thetadot1 = dt * thetaddot1;

    //Calculate thetaddots for k4
    thetaddot2 = calculateThetaddot2(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                            pendulum.theta1 + k3_theta1, pendulum.theta2 + k3_theta2,
                            pendulum.thetadot1 + k3_thetadot1, pendulum.thetadot2  + k3_thetadot2);

    thetaddot1 = calculateThetaddot1(pendulum.l1, pendulum.l2, pendulum.m1, pendulum.m2,
                                               pendulum.theta1 + k3_theta1, pendulum.theta2 + k3_theta2,
                                               pendulum.thetadot2  + k3_thetadot2, thetaddot2); 

    double k4_theta2 = dt * (pendulum.thetadot2 + k3_thetadot2);
    double k4_thetadot2 = dt * thetaddot2;
    double k4_theta1 = dt * (pendulum.thetadot1 + k3_thetadot1);
    double k4_thetadot1 = dt * thetaddot1;

    //Update properties based on RK4                                     
    pendulum.thetadot2 = pendulum.thetadot2 + ((k1_thetadot2 + 2 * k2_thetadot2 + 2 * k3_thetadot2 + k4_thetadot2) / 6);
    pendulum.theta2 = pendulum.theta2 + ((k1_theta2 + 2 * k2_theta2 + 2 * k3_theta2 + k4_theta2) / 6);

    pendulum.thetadot1 = pendulum.thetadot1 + ((k1_thetadot1 + 2 * k2_thetadot1 + 2 * k3_thetadot1 + k4_thetadot1) / 6);
    pendulum.theta1 = pendulum.theta1 + ((k1_theta1 + 2 * k2_theta1 + 2 * k3_theta1 + k4_theta1) / 6);

    //Update cartesian coordinates based on polar coordinates values for both masses
    pendulum.x1 = pendulum.x0 + ( pendulum.l1 * sin(pendulum.theta1)); 
    pendulum.y1 = pendulum.y0 - ( pendulum.l1 * cos(pendulum.theta1));

    pendulum.x2 = pendulum.x0 + ( pendulum.l1 * sin(pendulum.theta1)) + ( pendulum.l2 * sin(pendulum.theta2));
    pendulum.y2 = pendulum.y0 - ( pendulum.l1 * cos(pendulum.theta1)) - ( pendulum.l2 * cos(pendulum.theta2));

}