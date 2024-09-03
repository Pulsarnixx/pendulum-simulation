#include "timer.hpp"

#include <iostream>

std::shared_ptr<Timer> Timer::s_CoreTimer;
std::shared_ptr<Timer> Timer::s_ClientTimer;

void Timer::Init(){

    s_CoreTimer = std::make_shared<Timer>();
    s_ClientTimer = std::make_shared<Timer>();
}

void Timer::Start(){

    m_Start = std::chrono::steady_clock::now();
}

void Timer::Stop(){

    auto end = std::chrono::steady_clock::now(); //auto = std::chrono::time_point<std::chrono::steady_clock>
    m_Elapsed = end - m_Start;
}

void Timer::PrintElapsedTime(const std::string& title, TimeFormat format){

    if(format == TimeFormat::miliseconds){
        std::cout << "[" << title << "] " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(m_Elapsed).count() 
                  << " ms" << std::endl;
    }
    else if(format == TimeFormat::microseconds){
        std::cout << "[" << title << "] "  
                  << std::chrono::duration_cast<std::chrono::microseconds>(m_Elapsed).count() 
                  << " μs" << std::endl;
    }
    else{
        std::cout << "[" << title << "] "  
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(m_Elapsed).count() 
                  << " ns" << std::endl;
    }
       
}