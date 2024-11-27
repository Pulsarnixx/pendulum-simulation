#include "simulation2D.hpp"
#include "numerical_eq.hpp"

#include <memory>

#undef DEBUG

int main(){



    /*
        NUMERICAL TESTS FIRST
    */
#ifdef DEBUG
    RunTests();
#endif

    /*
        SIMULATION APP
    */
    std::unique_ptr<Simulation> sim = std::make_unique<Simulation2D>();

    sim->initialize();

    sim->run();

    sim->shutdown();


    return 0;
}