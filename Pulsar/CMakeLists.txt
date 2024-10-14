#------------SPDLOG--------------------------------
set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include/)
message(STATUS "[SPDLOG] include path:  ${SPDLOG_INCLUDE_DIR}")
#------------------------------------------------

#------------GLFW--------------------------------
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include/)
message(STATUS "[GLFW] include path:  ${GLFW_INCLUDE_DIR}")
#------------------------------------------------

#------------GLAD--------------------------------
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include/)
message(STATUS "[GLAD] include path:  ${GLAD_INCLUDE_DIR}")
#------------------------------------------------

#------------STB_IMAGE--------------------------------
set(STB_IMAGE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/)
message(STATUS "[STB_IMAGE] include path:  ${STB_IMAGE}")
#------------------------------------------------

#------------IMGUI--------------------------------
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/)
message(STATUS "[IMGUI] include path: ${IMGUI_INCLUDE_DIR}")
set(IMGUI_BACKENDS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/)
message(STATUS "[IMGUI] include path: ${IMGUI_BACKENDS_INCLUDE_DIR}")
#------------------------------------------------

#------------GTEST--------------------------------
set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest/include/)
message(STATUS "[GTEST] include path: ${GTEST_INCLUDE_DIR}")
#-------------------------------------------------

add_subdirectory(vendor)

#Include directories and libs for each module

#------------CORE--------------------------------
message(STATUS "[PULSARENGINE] Configuring pxcore module...")

set(CORE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core)
message(STATUS "[PULSARENGINE] pxcore include path: ${CORE_INCLUDE_PATH}")
file(GLOB_RECURSE CORE_SOURCES "${CORE_INCLUDE_PATH}/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "${CORE_INCLUDE_PATH}/*.hpp")

message(STATUS "Found source files:")
foreach(file ${CORE_SOURCES})
    message(STATUS "  ${file}")
endforeach()

message(STATUS "Found header files:")
foreach(file ${CORE_HEADERS})
    message(STATUS "  ${file}")
endforeach()
#------------------------------------------------

#------------GRAPHICS-----------------------------
message(STATUS "[PULSARENGINE] Configuring pxgraphics module...")

set(GRAPHICS_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/graphics)
message(STATUS "[PULSARENGINE] pxgraphics include path: ${GRAPHICS_INCLUDE_PATH}")
file(GLOB_RECURSE GRAPHICS_SOURCES "${GRAPHICS_INCLUDE_PATH}/*.cpp")
file(GLOB_RECURSE GRAPHICS_HEADERS "${GRAPHICS_INCLUDE_PATH}/*.hpp")

message(STATUS "Found source files:")
foreach(file ${GRAPHICS_SOURCES})
    message(STATUS "  ${file}")
endforeach()

message(STATUS "Found header files:")
foreach(file ${GRAPHICS_HEADERS})
    message(STATUS "  ${file}")
endforeach()
#------------------------------------------------

#----Unit testing--------------------------------
add_executable(tests tests/tests.cpp)
target_include_directories(tests PUBLIC ${GTEST_INCLUDE_DIR})
target_link_libraries(tests gtest_main)
set_target_properties( tests PROPERTIES 
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Pulsar/tests"
                    )
#------------------------------------------------

add_library( ${PROJECT_NAME} STATIC
             ${CORE_SOURCES} ${GRAPHICS_SOURCES}
)

target_include_directories( ${PROJECT_NAME} PUBLIC ${SPDLOG_INCLUDE_DIR} 
                            ${GLAD_INCLUDE_DIR}    ${GLFW_INCLUDE_DIR} 
                            ${IMGUI_INCLUDE_DIR}   ${STB_IMAGE}
                            ${IMGUI_BACKENDS_INCLUDE_DIR} ${CORE_INCLUDE_PATH}   
                            ${GRAPHICS_INCLUDE_PATH}
)

target_link_libraries( ${PROJECT_NAME} PUBLIC
                        glad glfw imgui stb_image
)

