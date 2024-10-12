#include "FPSTimer.hpp"

#include "../log/log.hpp" //logging

std::shared_ptr<FPSTimer> FPSTimer::s_FPSTimer;

//System access
void FPSTimer::Init(){
    s_FPSTimer = std::make_shared<FPSTimer>();
}

//Utilities
void FPSTimer::StartFrame(){
    m_Start = std::chrono::steady_clock::now();
    m_Frames++;
}

double FPSTimer::GetDeltaTime() const {
    return m_DeltaTime.count();
}

void FPSTimer::UpdateFPS(){

    auto stop = std::chrono::steady_clock::now();
    m_DeltaTime += (stop - m_Start);

    if(m_DeltaTime.count() >= 1.0){

        std::string s = "FPS: " + std::to_string(m_Frames) + " | Frames Time (avg) "
                         + std::to_string( (m_DeltaTime.count() / m_Frames ) * 1000.0f) + " ms"; 
        PX_CORE_TRACE(s);
        m_DeltaTime = std::chrono::duration<double>(0);
        m_Frames = 0;
    }

}