#include "numerical_eq.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>  // Do formatowania wyników (np. zaokrąglanie)

//Constanst
static double g = 9.81;
static double m = 1.0; 
static double l = 1.0; 

double CalculateKineticEnergyPendulum(double thetadot){
    return (0.5 * m * pow(l,2) * pow(thetadot,2));
}

double CalculatePotentialEnergyPendulum(double thetha){
    return ( m * g * l * (1 - cos(thetha)));
}

Data PendulumApprox(double dt, double theta, double thetadot){

    //Calculate properties in polar coordinates
    double thethaddot = -(g / l) * theta;
    thetadot += (thethaddot * dt);    
    theta += (thetadot * dt);

    return {theta, thetadot};
}

Data PendulumEuler(double dt, double theta, double thetadot){

    //Calculate properties in polar coordinates
    double thethaddot = -(g / l) * sin(theta);
    thetadot += (thethaddot * dt);    
    theta += (thetadot * dt);

    return {theta, thetadot};
}

void TestPendulumApproxToFile(const char* file_name, double t0, double tmax, double dt, double thetha0, double thetadot0){
    
    std::ofstream outfile(file_name);

    if (!outfile.is_open()) {
        std::cerr << "Can't open file!" << std::endl;
        return;
    }

    double t = t0;
    double theta = thetha0;
    double thetadot = thetadot0;
    double k_energy = CalculateKineticEnergyPendulum(thetadot0);
    double p_energy = CalculatePotentialEnergyPendulum(thetha0);
    double total_energy = k_energy + p_energy;

    outfile << std::setw(10) << "time [s]"
            << std::setw(12) << "theta [rad]"
            << std::setw(18) << "thetadot [rad/s]"
            << std::setw(12) << "k_energy"
            << std::setw(12) << "p_energy"
            << std::setw(15) << "total_energy" << "\n";

    while (t < tmax) {
        Data data = PendulumApprox(dt, theta, thetadot);

        t += dt;
        theta = data.data1;
        thetadot = data.data2;
        k_energy = CalculateKineticEnergyPendulum(thetadot);
        p_energy = CalculatePotentialEnergyPendulum(theta);
        total_energy = k_energy + p_energy;

        outfile << std::setw(10) << std::fixed << std::setprecision(5) << t
                << std::setw(12) << std::fixed << std::setprecision(5) << theta
                << std::setw(18) << std::fixed << std::setprecision(5) << thetadot
                << std::setw(12) << std::fixed << std::setprecision(5) << k_energy
                << std::setw(12) << std::fixed << std::setprecision(5) << p_energy
                << std::setw(15) << std::fixed << std::setprecision(5) << total_energy << "\n";
    }

    outfile.close();
}

void TestPendulumEulerToFile(const char* file_name, double t0, double tmax, double dt, double thetha0, double thetadot0){
    
    std::ofstream outfile(file_name);

    if (!outfile.is_open()) {
        std::cerr << "Can't open file!" << std::endl;
        return;
    }

    double t = t0;
    double theta = thetha0;
    double thetadot = thetadot0;
    double k_energy = CalculateKineticEnergyPendulum(thetadot0);
    double p_energy = CalculatePotentialEnergyPendulum(thetha0);
    double total_energy = k_energy + p_energy;

    outfile << "\t" << "time [s]"
            << "\t" << "theta [rad]"
            << "\t" << "thetadot [rad/s]"
            << "\t" << "k_energy"
            << "\t" << "p_energy"
            << "\t" << "total_energy" << "\n";

    while (t < tmax) {

        Data data = PendulumEuler(dt, theta, thetadot);

        t += dt;
        theta = data.data1;
        thetadot = data.data2;
        k_energy = CalculateKineticEnergyPendulum(thetadot);
        p_energy = CalculatePotentialEnergyPendulum(theta);
        total_energy = k_energy + p_energy;
        
        outfile << "\t" << std::fixed << std::setprecision(5) << t
                << "\t" << std::fixed << std::setprecision(5) << theta
                << "\t" << std::fixed << std::setprecision(5) << thetadot
                << "\t" << std::fixed << std::setprecision(5) << k_energy
                << "\t" << std::fixed << std::setprecision(5) << p_energy
                << "\t" << std::fixed << std::setprecision(5) << total_energy << "\n";
    }

    outfile.close();
}

void RunTests(){

    TestPendulumApproxToFile("approx.txt", 0.0, 10.0, 0.01, (30.0 * M_PI)/ 180.0 , 0.0f); //30 stopni
    TestPendulumEulerToFile("euler.txt", 0.0, 10.0, 0.01, (30.0 * M_PI)/ 180.0 , 0.0f); //30 stopni
}