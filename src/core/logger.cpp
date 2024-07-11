#include "logger.hpp"

#include <stdio.h>

//Colours for printf, fprintf ...
#define ORANGE  "\033[38;5;214m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"

Logger::Logger(){
    printf("[LOGGER] Constructor\n");
    //TODO: Creating log file
}

Logger::~Logger(){
    printf("[LOGGER] Destructor\n");
}

std::string Logger::GetLogLevelString(LogLevel level){

    switch (level)
    {
        case LogLevel::DEBUG : return "DEBUG"; break;
        case LogLevel::INFO  : return "INFO"; break;
        case LogLevel::ERROR : return "ERROR"; break;
        default: return ""; break;
    }
}

std::string Logger::GetCurrentTime(){

    //TODO: Modify in the future for std:string / std::sstream
    time_t now = time(0); 
    tm* timeInfo = localtime(&now); 

    char buffer[20]; 
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo); 

    return std::string(buffer);

}

void Logger::ColorLogLevelString(std::string & loglevel){

    if(loglevel == "DEBUG")
        loglevel = ORANGE+loglevel+WHITE;
    else if(loglevel == "ERROR")
        loglevel = RED+loglevel+WHITE;

}

void Logger::log(LogLevel level, const std::string &mess){
 

#ifdef DEBUG_ON
    std::string timestamp   = GetCurrentTime();
    std::string levelString = GetLogLevelString(level);
    
    ColorLogLevelString(levelString);

    fprintf(stdout,"[%s] %s: %s\n",timestamp.c_str(),levelString.c_str(),mess.c_str());
#endif


}