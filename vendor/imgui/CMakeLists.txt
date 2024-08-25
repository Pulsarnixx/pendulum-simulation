#Define all imgui cpp files
file(GLOB IMGUI_SRC
    ${IMGUI_SOURCE_DIR}/*.cpp
)

#Define all imgui .h files
file(GLOB IMGUI_INC
    ${IMGUI_INCLUDE_DIR}/*.h
)

add_library(
        imgui STATIC 
        ${IMGUI_SRC}
        ${IMGUI_INC})

target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})