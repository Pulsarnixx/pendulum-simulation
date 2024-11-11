#pragma once

#include "simulation.hpp"

/*
    Class that represent simulation 2D which provide 
    pulsar system and pulsar graphics
*/

class Simulation2D : public Simulation {


public:
    Simulation2D() = default;
    ~Simulation2D() = default;

    virtual void initialize() override;  
    virtual void run() override;  
    virtual void shutdown() override; 
};