#pragma once

#include "time_util.hpp"

/*
    FPSTimer class singleton to count frames and elapsed time
    in main loop
*/
class FPSTimer{

public:

    //Constr & Destruct
    FPSTimer():m_DeltaTime(0),m_Frames(0){};
    ~FPSTimer() = default;

    //Copy constr.
    FPSTimer(const FPSTimer&) = delete;
    FPSTimer& operator=(const FPSTimer&) = delete;

    //Move constr.
    FPSTimer(FPSTimer&&) = delete;
    FPSTimer& operator=(FPSTimer&&) = delete;

    //System Access
    static void Init();
    inline static std::shared_ptr<FPSTimer>& GetTimer()  { return s_FPSTimer; }

    //Utilites
    void StartFrame();
    double GetDeltaTime() const ;
    void UpdateFPS();

private:
    static std::shared_ptr<FPSTimer> s_FPSTimer;

    std::chrono::time_point<std::chrono::steady_clock> m_Start;
    std::chrono::duration<double> m_DeltaTime;
    unsigned int m_Frames;
    
};//class FPSTimer