cmake_minimum_required(VERSION 3.21)

project(pulsar)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")

#Pulsar engine include path and lib`
set(PULSAR_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Pulsar)
message(STATUS "[PULSARENGINE] Engine include path: ${PULSAR_INCLUDE_PATH}")

add_subdirectory(Pulsar)
add_subdirectory(App)