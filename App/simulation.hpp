#pragma once 

/*
    Interface used to 
*/
class Simulation{

public:
    virtual ~Simulation() {}

    virtual void initialize() = 0;  
    virtual void run() = 0;  
    virtual void shutdown() = 0; 

};