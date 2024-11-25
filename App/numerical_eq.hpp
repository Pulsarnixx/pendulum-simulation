#pragma once

#include <string> //std::string

struct PendulumData{
    double theta;
    double thetadot;
};

struct DoublePendulumData{
    double theta1;
    double theta2;
    double thetadot1;
    double thetadot2;
};

double CalculateKineticEnergyPendulum(double thetadot);
double CalculatePotentialEnergyPendulum(double thetha);


PendulumData PendulumApprox(double dt, double theta, double thetadot);
PendulumData PendulumEuler(double dt, double theta, double thetadot);
DoublePendulumData DoublePendulumEuler( double dt, double l1, double l2, double m1, double m2,
                                        double thetha1,double thetha2, double thetadot1, double thetadot2);


void TestPendulumApproxToFile(const std::string& file_name, double t0, double tmax, double dt, double thetha0, double thetadot0);
void TestPendulumEulerToFile(const std::string& file_name, double t0, double tmax, double dt, double thetha0, double thetadot0);

void TestDoublePendulumEulerToFile( const std::string& file_name, double t0, double tmax, double dt, 
                                    double l1, double l2, double m1, double m2,
                                    double thetha1_0, double thetadot1_0, double thetha2_0, double thetadot2_0);


void RunTests();


