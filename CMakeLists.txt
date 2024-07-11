cmake_minimum_required(VERSION 3.21)

project(pulsarEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")

#GLFW and GLAD
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
message(STATUS "[GLAD] Include Path: ${GLAD_INCLUDE_DIR}")
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
message(STATUS "[GLFW] Include Path: ${GLFW_INCLUDE_DIR}")

add_subdirectory(vendor)
add_subdirectory(src)