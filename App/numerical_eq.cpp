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

#define TEST_FOLDER_PATH "/home/marek/Dev/Projects/pulsarEngine/tests_results/"


void RunTests(){

    TestPendulumApproxToFile("approx.txt", 0.0, 10.0, 0.01, (30.0 * M_PI)/ 180.0 , 0.0f); //30 stopni
    TestPendulumEulerToFile("euler.txt", 0.0, 10.0, 0.01, (30.0 * M_PI)/ 180.0 , 0.0f); //30 stopni
    TestDoublePendulumEulerToFile( "double_euler.txt", 0.0, 10.0, 0.016, 
                                   0.3, 0.3, 0.1, 0.1, (180.0 * M_PI)/ 180.0, (180.0 * M_PI)/ 180.0, 0.0, 0.0);
}


double CalculateKineticEnergyPendulum(double thetadot){
    return (0.5 * m * pow(l,2) * pow(thetadot,2));
}

double CalculatePotentialEnergyPendulum(double theta){
    return ( m * g * l * (1 - cos(theta)));
}

double CalculateKineticEnergyDoublePendulum(double l1, double l2, double m1, double m2, double theta1, double theta2, double thetadot1, double thetadot2){
    return ( ( 0.5 * m1 * l1 * l1 * thetadot1 * thetadot1 ) + 
             ( 0.5 * m2 * ( (l1 * l1 * thetadot1 * thetadot1) + (l2 * l2 * thetadot2 * thetadot2) + (2 * l1 * l2 * thetadot1 * thetadot2 * cos(theta1 - theta2)) ) )
            );
}

double CalculatePotentialEnergyDoublePendulum(double l1, double l2, double m1, double m2, double theta1, double theta2){
    return (   (-1.0 * m1 * g * l1 * cos(theta1)) - ( m1 * g * ( (l1 * cos(theta1)) + (l2 * cos(theta2)) ) )
             
             );
}

PendulumData PendulumApprox(double dt, double theta, double thetadot){

    //Calculate properties in polar coordinates
    double thetaddot = -(g / l) * theta;
    thetadot += (thetaddot * dt);    
    theta += (thetadot * dt);

    return {theta, thetadot};
}

PendulumData PendulumEuler(double dt, double theta, double thetadot){

    //Calculate properties in polar coordinates
    double thetaddot = -(g / l) * sin(theta);
    thetadot += (thetaddot * dt);    
    theta += (thetadot * dt);

    return {theta, thetadot};
}

DoublePendulumData DoublePendulumEuler( double dt, double l1, double l2, double m1, double m2,
                                        double theta1,double theta2, double thetadot1, double thetadot2){

    //Calculate properties in polar coordinates
    double a = ( -1 * (m1 + m2) * g * sin(theta1) ) -( m2 * l2 * thetadot2 * thetadot2 * sin(theta1 - theta2) );
    double b = (m1 + m2) * l1;
    double c = m2 * l2 * cos(theta1 - theta2);
    double d = -1 * g * sin(theta2) + pow(thetadot1,2) * l1 * sin(theta1 - theta2);
    double e = l1 * cos(theta1 - theta2);
    double f = l2;

    //Calculate properties in polar coordinates for both masses
    double thetaddot2 = (d - (e * a)) / (f - (e*c));
    double thetaddot1 = (a - (c * thetaddot2)) / b;

    thetadot2 = thetadot2 + dt * thetaddot2;
    theta2 = theta2 + dt * thetadot2;

    thetadot1 = thetadot1 + dt * thetaddot1;
    theta1 = theta1 + dt * thetadot1;

    return {theta1, theta2, thetaddot1, thetaddot2};
}

void TestPendulumApproxToFile(const std::string&  file_name, double t0, double tmax, double dt, double theta0, double thetadot0){
    
    std::string file_path = TEST_FOLDER_PATH + file_name;
    std::ofstream outfile(file_path);

    if (!outfile.is_open()) {
        std::cerr << "Can't open file!" << std::endl;
        return;
    }

    double t = t0;
    double theta = theta0;
    double thetadot = thetadot0;
    double k_energy = CalculateKineticEnergyPendulum(thetadot0);
    double p_energy = CalculatePotentialEnergyPendulum(theta0);
    double total_energy = k_energy + p_energy;

    outfile << "\t" << "t [s]"
            << "\t" << "theta [rad]"
            << "\t" << "thetadot [rad/s]"
            << "\t" << "E_k"
            << "\t" << "E_p"
            << "\t" << "E_k + E_p" << "\n";


    while (t < tmax) {
        PendulumData data = PendulumApprox(dt, theta, thetadot);

        t += dt;
        theta = data.theta;
        thetadot = data.thetadot;
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

void TestPendulumEulerToFile(const std::string&  file_name, double t0, double tmax, double dt, double theta0, double thetadot0){
    
    std::string file_path = TEST_FOLDER_PATH + file_name;
    std::ofstream outfile(file_path);

    if (!outfile.is_open()) {
        std::cerr << "Can't open file!" << std::endl;
        return;
    }

    double t = t0;
    double theta = theta0;
    double thetadot = thetadot0;
    double k_energy = CalculateKineticEnergyPendulum(thetadot0);
    double p_energy = CalculatePotentialEnergyPendulum(theta0);
    double total_energy = k_energy + p_energy;

    outfile << "\t" << "t [s]"
            << "\t" << "theta [rad]"
            << "\t" << "thetadot [rad/s]"
            << "\t" << "E_k"
            << "\t" << "E_p"
            << "\t" << "E_k + E_p" << "\n";

    while (t < tmax) {

        PendulumData data = PendulumEuler(dt, theta, thetadot);

        t += dt;
        theta = data.theta;
        thetadot = data.thetadot;
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

void TestDoublePendulumEulerToFile( const std::string&  file_name, double t0, double tmax, double dt, 
                                    double l1, double l2, double m1, double m2,
                                    double theta1_0, double theta2_0, double thetadot1_0, double thetadot2_0)
{

    std::string file_path = TEST_FOLDER_PATH + file_name;
    std::ofstream outfile(file_path);

    if (!outfile.is_open()) {
        std::cerr << "Can't open file!" << std::endl;
        return;
    }

    double t = t0;
    double theta1 = theta1_0;
    double theta2 = theta2_0;
    double thetadot1 = thetadot1_0;
    double thetadot2 = thetadot2_0;
    double k_energy = CalculateKineticEnergyDoublePendulum(l1,l2,m1,m2,theta1,theta2,thetadot1,thetadot2);
    double p_energy = CalculatePotentialEnergyDoublePendulum(l1,l2,m1,m2,theta1,theta2);
    double total_energy = k_energy + p_energy;

    outfile << "\t" << "t [s]" 
            << "\t" << "ϴ1" 
            << "\t" << "ϴ2"
            << "\t" << "ϴd1"
            << "\t" << "ϴd2"
            << "\t" << "Ek"
            << "\t" << "Ep"
            << "\t" << "Ec" << "\n";

        
    outfile << "\t" << std::fixed << std::setprecision(10) << t
            << "\t" << std::fixed << std::setprecision(10) << theta1
            << "\t" << std::fixed << std::setprecision(10) << theta2
            << "\t" << std::fixed << std::setprecision(10) << thetadot1
            << "\t" << std::fixed << std::setprecision(10) << thetadot2
            << "\t" << std::fixed << std::setprecision(10) << k_energy
            << "\t" << std::fixed << std::setprecision(10) << p_energy
            << "\t" << std::fixed << std::setprecision(10) << total_energy  << "\n";

    while (t < tmax) {

        DoublePendulumData data = DoublePendulumEuler(dt, l1, l2, m1, m2, theta1, theta2, thetadot1, thetadot2);

        t += dt;
        theta1 = data.theta1;
        theta2 = data.theta2;
        thetadot1 = data.thetadot1;
        thetadot2 = data.thetadot2;
        k_energy = CalculateKineticEnergyDoublePendulum(l1,l2,m1,m2,theta1,theta2,thetadot1,thetadot2);
        p_energy = CalculatePotentialEnergyDoublePendulum(l1,l2,m1,m2,theta1,theta2);
        total_energy = k_energy + p_energy;
        
        outfile << "\t" << std::fixed << std::setprecision(10) << t
                << "\t" << std::fixed << std::setprecision(10) << theta1
                << "\t" << std::fixed << std::setprecision(10) << theta2
                << "\t" << std::fixed << std::setprecision(10) << thetadot1
                << "\t" << std::fixed << std::setprecision(10) << thetadot2 
                << "\t" << std::fixed << std::setprecision(10) << k_energy
                << "\t" << std::fixed << std::setprecision(10) << p_energy
                << "\t" << std::fixed << std::setprecision(10) << total_energy  << "\n";
    }

    outfile.close();
  
}
