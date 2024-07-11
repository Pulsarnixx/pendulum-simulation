#pragma once

/*
    Logging system for debugging purpose. Temporary its only stdout/stderr.

    inspired by: https://www.geeksforgeeks.org/logging-system-in-cpp/
*/
#include <string>

enum LogLevel { DEBUG, INFO, ERROR };

//Singleton
class Logger {
    public:

        //Copy constr.
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        //Move constr.
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        //Access
        static Logger& getLogger() {
            static Logger logger;
            return logger;
        }

        //Utilities
        void log(LogLevel level, const std::string &mess);

    private:
        //Constr. & Destr.
        Logger();
        ~Logger();

        //Utilities
        std::string GetLogLevelString(LogLevel level);
        std::string GetCurrentTime();
        void ColorLogLevelString(std::string & loglevel);


};