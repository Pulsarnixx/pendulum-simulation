cmake_minimum_required(VERSION 3.21)

project(pulsarEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")

# set(VENDOR_PATH "${CMAKE_SOURCE_DIR}/vendor")

# add_subdirectory(vendor)
add_subdirectory(src)