#------------GLFW--------------------------------
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
message(STATUS "[GLFW] include path:  ${GLFW_INCLUDE_DIR}")
#------------------------------------------------

#------------GLAD--------------------------------
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
message(STATUS "[GLAD] include path:  ${GLAD_INCLUDE_DIR}")
#------------------------------------------------

#------------IMGUI--------------------------------
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
message(STATUS "[IMGUI] include Path: ${IMGUI_INCLUDE_DIR}")
set(IMGUI_BACKENDS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends)
message(STATUS "[IMGUI] include Path: ${IMGUI_BACKENDS_INCLUDE_DIR}")
#------------------------------------------------

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

add_library( ${PROJECT_NAME} STATIC
             ${CORE_SOURCES} ${GRAPHICS_SOURCES}
)

target_include_directories( ${PROJECT_NAME} PUBLIC
                            ${GLAD_INCLUDE_DIR}  ${GLFW_INCLUDE_DIR} 
                            ${IMGUI_INCLUDE_DIR} ${IMGUI_BACKENDS_INCLUDE_DIR} 
                            ${CORE_INCLUDE_PATH} ${GRAPHICS_INCLUDE_PATH}
)

target_link_libraries( ${PROJECT_NAME} PUBLIC
                        glad glfw imgui
)

