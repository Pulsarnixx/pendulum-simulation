#pragma once

//Headers used by all timers
#include <memory> // std::shared_ptr
#include <chrono> // std::time_point, measuring time

//Time format used by all timers
enum TimeFormat { mili, micro, nano };
