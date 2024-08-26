#include "log.hpp"

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init(){

    //Formating log message globally for all loggers. See spdlog docs.
    spdlog::set_pattern("%^[%T] %n: %v%$");

    //Creating loggers
    s_CoreLogger = spdlog::stdout_color_mt("Pulsar");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("App");
    s_ClientLogger->set_level(spdlog::level::trace);
}