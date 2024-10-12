#pragma once

#include "time_util.hpp"

/*
    GlobalTimer singleton class to manage all functionality of engine to one timer
*/
class GlobalTimer{

public:

    //Constr & Destruct
    GlobalTimer()  = default;
    ~GlobalTimer() = default;

    //Copy constr.
    GlobalTimer(const GlobalTimer&) = delete;
    GlobalTimer& operator=(const GlobalTimer&) = delete;

    //Move constr.
    GlobalTimer(GlobalTimer&&) = delete;
    GlobalTimer& operator=(GlobalTimer&&) = delete;

    //System Access
    static void Init();
    inline static std::shared_ptr<GlobalTimer>& GetTimer()  { return s_GlobalTimer; }

    //Utilites
    void Start();
    double GetElapsedTime() const ;

private:
    static std::shared_ptr<GlobalTimer> s_GlobalTimer;

    std::chrono::time_point<std::chrono::steady_clock> m_Start;
    
};//class GlobalTimer