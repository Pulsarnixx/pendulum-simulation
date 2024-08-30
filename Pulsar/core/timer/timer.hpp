#pragma once

class Timer{

public:

    static void Init();

private:
    
    static double startTime;
    static double endTime;
    static double elapsedTime;
};

//Core side log
// #define PX_CORE_TIMER_START(...) 
// #define PX_CORE_TIMER_END(...)   

//Client side log
// #define PX_CLIENT_TIMER_START(...) 
// #define PX_CLIENT_TIMER_END(...)   
