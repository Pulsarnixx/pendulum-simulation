#pragma once

struct Data{
    double data1;
    double data2;
};

double CalculateKineticEnergyPendulum(double thetadot);
double CalculatePotentialEnergyPendulum(double thetha);


Data PendulumApprox(double dt, double theta, double thetadot);
Data PendulumEuler(double dt, double theta, double thetadot);


void TestPendulumApproxToFile(const char* file_name, double t0, double tmax, double dt, double thetha0, double thetadot0);
void TestPendulumEulerToFile(const char* file_name, double t0, double tmax, double dt, double thetha0, double thetadot0);

void TestDoublePendulumEulerToFile( const char* file_name, double t0, double tmax, double dt, 
                                    double l1, double l2, double m1, double m2,
                                    double thetha1_0, double thetadot1_0, double thetha2_0, double thetadot2_0);


void RunTests();


