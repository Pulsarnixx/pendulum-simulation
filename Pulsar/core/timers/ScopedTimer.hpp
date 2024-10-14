#pragma once

#include "time_util.hpp"
#include "glad.h" //gl functions

class ScopedTimer{

public:
        //Constr & Destruct
        ScopedTimer()  = default;
        ~ScopedTimer() = default;

        //Copy constr.
        ScopedTimer(const ScopedTimer&) = delete;
        ScopedTimer& operator=(const ScopedTimer&) = delete;

        //Move constr.
        ScopedTimer(ScopedTimer&&) = delete;
        ScopedTimer& operator=(ScopedTimer&&) = delete;
        
        //System Access
        static void Init();
        inline static std::shared_ptr<ScopedTimer>& GetTimer()  { return s_ScopeTimer; }

        //Utilites
        void StartMeasure();
        double StopMeasure() const ;

        void StartMeasureGL() { glFinish(); StartMeasure(); } 
        double StopMeasureGL() const { glFinish(); return StopMeasure(); } 

private:
    static std::shared_ptr<ScopedTimer> s_ScopeTimer;
    std::chrono::time_point<std::chrono::steady_clock> m_Start;
};//class ScopedTimer


//Core side timer
#define PX_CORE_TIMER_START  ScopedTimer::GetTimer()->StartMeasure()
#define PX_CORE_TIMER_STOP   ScopedTimer::GetTimer()->StopMeasure()

#define PX_CORE_TIMER_START_GL  ScopedTimer::GetTimer()->StartMeasureGL()
#define PX_CORE_TIMER_STOP_GL   ScopedTimer::GetTimer()->StopMeasureGL()

//Client side timer
#define PX_CLIENT_TIMER_START   ScopedTimer::GetTimer()->StartMeasure()
#define PX_CLIENT_TIMER_STOP    ScopedTimer::GetTimer()->StopMeasure()