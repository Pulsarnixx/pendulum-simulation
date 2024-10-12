#include "ScopedTimer.hpp"

std::shared_ptr<ScopedTimer> ScopedTimer::s_ScopeTimer;

//System access
void ScopedTimer::Init(){
    s_ScopeTimer = std::make_shared<ScopedTimer>();
}

//Utilities
void ScopedTimer::StartMeasure(){
    m_Start = std::chrono::steady_clock::now();
}

double ScopedTimer::StopMeasure() const {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(now - m_Start).count();
}
