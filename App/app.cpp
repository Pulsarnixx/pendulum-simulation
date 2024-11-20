#include "simulation2D.hpp"
#include "numerical_eq.hpp"
// #include "simulation3D.hpp"

#include <cstdio> //fprintf
#include <memory>

void Error(const char* message){ fprintf(stderr, message); }

int main(int argc, char* argv[]){

    if (argc != 2) {
        Error("Wrong number of arguments!\n");
        return 1;
    }

    if (*argv[1] != '1' && *argv[1] != '2') {
        Error("Wrong option! 1 - 2D simulation, 2 - 3D simulation\n");
        return 1;
    }

    /*
        TEST FIRST
    */
    RunTests();


    char choise = *argv[1];
    std::unique_ptr<Simulation> sim;

    switch (choise)
    {
        case '1': sim = std::make_unique<Simulation2D>();  break;
        // case '2': sim = std::make_unique<Simulation3D>();  break;
        
        default: break;
    }

    
    sim->initialize();

    sim->run();

    sim->shutdown();


    return 0;
}