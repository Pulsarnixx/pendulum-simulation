#pragma once

struct SinglePendulum{

    //Properties
    float m;                //Masses [kg]
    float r;                //Diameter of masses
    
    //Polar coordinates for physical calculations
    float l;                //Rods length [m]
    float thetha;           //Angles [rad]
    float thethadot;        //Angular velocity [rad/s]

    //Cartesian coordinates for OpenGL 
    float x,y;
  
};

struct DoublePendulum{
    
    //Properties
    float m1,m2;                //Masses [kg]
    float r1,r2;                //Diameter of masses
    
    //Polar coordinates for physical calculations
    float l1,l2;                    //Rods length [m]
    float thetha1, thetha2;         //Angles [rad]
    float thethadot1,thethadot2;    //Angular velocity [rad/s]

    //Cartesian coordinates for OpenGL 
    float x1,y1;
    float x2,y2;

};

void InitPendulum(float x0, float y0, SinglePendulum& pendulum);
void InitDoublePendulum(float x0, float y0, DoublePendulum& pendulum);