#pragma once

struct SinglePendulum{

    //Properties
    double m;                //Masses [kg]
    
    //Polar coordinates for physical calculations
    double l;               //Rods length [m]
    double theta;           //Angles [rad]
    double thetadot;        //Angular velocity [rad/s]

    //Cartesian coordinates for OpenGL. Also float becasue OpenGL 
    float x0,y0;
    float x,y;

    SinglePendulum(float x0, float y0, double m, double l, double init_theta, double init_thetadot);

    void displayParameters();
  
};

struct DoublePendulum{
    
    //Properties
    double m1,m2;                //Masses [kg]
    
    //Polar coordinates for physical calculations
    double l1,l2;                    //Rods length [m]
    double theta1, theta2;         //Angles [rad]
    double thetadot1,thetadot2;    //Angular velocity [rad/s]

    //Cartesian coordinates for OpenGL
    float x0,y0;
    float x1,y1;
    float x2,y2;

    DoublePendulum( float x0, float y0, double m1, double m2, double l1, double l2, double init_theta1,
                    double init_theta2,double init_thetadot1, double init_thetadot2);

    void displayParameters();


};

void ResetPendulum(SinglePendulum& pendulum);
void ResetPendulum(DoublePendulum& pendulum);

/*
    Single Pendulum
*/
void SimulatePendulumApprox(SinglePendulum& pendulum);
void SimulatePendulumEuler(SinglePendulum& pendulum);
void SimulatePendulumRK2(SinglePendulum& pendulum);
void SimulatePendulumRK4(SinglePendulum& pendulum);

/*
    Double pendulum
*/
void SimulatePendulumEuler(DoublePendulum& pendulum);