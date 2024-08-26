message(STATUS "[PULSARENGINE] Configuring IMGUI module...")

message(STATUS "[PULSARENGINE] IMGUI include path: ${IMGUI_INCLUDE_DIR}")
file(GLOB_RECURSE IMGUI_SOURCES "${IMGUI_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE IMGUI_HEADERS "${IMGUI_INCLUDE_DIR}/*.h")

message(STATUS "Found source files:")
foreach(file ${IMGUI_SOURCES})
    message(STATUS "  ${file}")
endforeach()

message(STATUS "Found header files:")
foreach(file ${IMGUI_HEADERS})
    message(STATUS "  ${file}")
endforeach()

add_library(
        imgui STATIC 
        ${IMGUI_SOURCES}
        ${IMGUI_HEADERS})

target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})