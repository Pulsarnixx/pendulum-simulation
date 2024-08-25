cmake_minimum_required(VERSION 3.21)

project(exampleApp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")

#GLFW
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
message(STATUS "[GLAD] Include Path:  ${GLAD_INCLUDE_DIR}")

#GLAD
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
message(STATUS "[GLFW] Include Path:  ${GLFW_INCLUDE_DIR}")

#IMGUI
set(IMGUI_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/src)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/include)
message(STATUS "[IMGUI] Source Path:  ${IMGUI_SOURCE_DIR}")
message(STATUS "[IMGUI] Include Path: ${IMGUI_INCLUDE_DIR}")

#GTEST --- TODO
# message(STATUS "[Google Test] Fetching...")
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )

#PulsarEngine paths of each lib

#pxcore
set(CORE_LIB_NAME pxcore)
set(CORE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core)
message(STATUS "[PULSARENGINE] ${CORE_LIB_NAME} Include Path: ${CORE_INCLUDE_PATH}")

#pxgraphics
set(GRAPHICS_LIB_NAME pxgraphics)
set(GRAPHICS_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/graphics)
message(STATUS "[PULSARENGINE] ${GRAPHICS_LIB_NAME} Include Path: ${GRAPHICS_INCLUDE_PATH}")


add_subdirectory(vendor)
add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(example)