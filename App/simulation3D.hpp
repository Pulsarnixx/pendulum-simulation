#pragma once

#include "simulation.hpp"

/*
    Class that represent simulation 2D which provide 
    pulsar system and pulsar graphics
*/

class Simulation3D : public Simulation {


public:
    Simulation3D() = default;
    ~Simulation3D() = default;

    virtual void initialize() override;  
    virtual void run() override;  
    virtual void shutdown() override; 
};