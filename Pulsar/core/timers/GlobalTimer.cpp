#include "GlobalTimer.hpp"


std::shared_ptr<GlobalTimer> GlobalTimer::s_GlobalTimer;

//System access
void GlobalTimer::Init(){
    s_GlobalTimer = std::make_shared<GlobalTimer>();
}

//Utilities
void GlobalTimer::Start(){
    m_Start = std::chrono::steady_clock::now();
}

double GlobalTimer::GetElapsedTime() const {

    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(now - m_Start).count();
}