#pragma once

#include <memory> // std::shared_ptr
#include <chrono> // std::time_point, measuring time


enum TimeFormat { miliseconds, microseconds, nanoseconds };
/*
    Timer class that give you measurment utilities
*/
class Timer{

public:

    //Constr & Destruct
    Timer()  = default;
    ~Timer() = default;

    //Copy constr.
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    //Move constr.
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

    //System Access
    static void Init();
    inline static std::shared_ptr<Timer>& GetCoreTimer()   { return s_CoreTimer; }
    inline static std::shared_ptr<Timer>& GetClientTimer() { return s_ClientTimer; }

    //Utilities
    void Start();
    void Stop();
    void PrintElapsedTime(const std::string& title, TimeFormat format);

private:

    static std::shared_ptr<Timer> s_CoreTimer;
	static std::shared_ptr<Timer> s_ClientTimer;
    
    //Fields used to calculate time for each object of Timer
    std::chrono::time_point<std::chrono::steady_clock> m_Start;
    std::chrono::duration<double> m_Elapsed; 
};

//Core side log
#define PX_CORE_TIMER_START(...)  Timer::GetCoreTimer()->Start();
#define PX_CORE_TIMER_STOP_MILI(...)   Timer::GetCoreTimer()->Stop();\
                                       Timer::GetCoreTimer()->PrintElapsedTime(__VA_ARGS__,TimeFormat::miliseconds);

#define PX_CORE_TIMER_STOP_MICRO(...)   Timer::GetCoreTimer()->Stop();\
                                        Timer::GetCoreTimer()->PrintElapsedTime(__VA_ARGS__,TimeFormat::microseconds);

#define PX_CORE_TIMER_STOP_NANO(...)   Timer::GetCoreTimer()->Stop();\
                                       Timer::GetCoreTimer()->PrintElapsedTime(__VA_ARGS__,TimeFormat::nanoseconds);

//Client side log
#define PX_CLIENT_TIMER_START(...)   Timer::GetClientTimer()->Start();
#define PX_CLIENT_TIMER_STOP(...)    Timer::GetClientTimer()->Stop();  

#define PX_CLIENT_TIMER_STOP_MILI(...)   Timer::GetCoreTimer()->Stop();\
                                         Timer::GetCoreTimer()->PrintElapsedTime(__VA_ARGS__,TimeFormat::miliseconds);

#define PX_CLIENT_TIMER_STOP_MICRO(...)   Timer::GetCoreTimer()->Stop();\
                                          Timer::GetCoreTimer()->PrintElapsedTime(__VA_ARGS__,TimeFormat::microseconds);

#define PX_CLIENT_TIMER_NANO(...)      Timer::GetCoreTimer()->Stop();\
                                       Timer::GetCoreTimer()->PrintElapsedTime(__VA_ARGS__,TimeFormat::nanoseconds);
