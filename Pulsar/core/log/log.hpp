#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Log{

public:

    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
    
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;

};

/*
    TODO:
    Writing maths via logger
*/

//Core side log
#define PX_CORE_TRACE(...)    Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_CORE_INFO(...)     Log::GetCoreLogger()->info(__VA_ARGS__)
#define PX_CORE_WARN(...)     Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_CORE_ERROR(...)    Log::GetCoreLogger()->error(__VA_ARGS__)


//Client side log
#define PX_TRACE(...)    Log::GetClientLogger()->trace(__VA_ARGS__)
#define PX_INFO(...)     Log::GetClientLogger()->info(__VA_ARGS__)
#define PX_WARN(...)     Log::GetClientLogger()->warn(__VA_ARGS__)
#define PX_ERROR(...)    Log::GetClientLogger()->error(__VA_ARGS__)