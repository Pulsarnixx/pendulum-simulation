#include "simulation2D.hpp"
#include "numerical_eq.hpp"
// #include "simulation3D.hpp"

#include <memory>

int main(){



    /*
        NUMERICAL TESTS FIRST
    */
    RunTests();

    /*
        SIMULATION APP
    */
    std::unique_ptr<Simulation> sim = std::make_unique<Simulation2D>();

    sim->initialize();

    sim->run();

    sim->shutdown();


    return 0;
}