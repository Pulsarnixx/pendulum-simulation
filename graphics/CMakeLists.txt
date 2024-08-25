#Creating lib
add_library(${GRAPHICS_LIB_NAME} STATIC
            window/window.cpp window/window.hpp
            renderer/renderer.cpp renderer/renderer.hpp
            widget/gui.cpp widget/gui.hpp
            pxgraphics.cpp pxgraphics.hpp
)

#Including .h files and other libs
target_include_directories( ${GRAPHICS_LIB_NAME} PUBLIC 
                            ${GLAD_INCLUDE_DIR}  ${GLFW_INCLUDE_DIR} 
                            ${IMGUI_INCLUDE_DIR} ${CORE_INCLUDE_PATH})

target_link_libraries( ${GRAPHICS_LIB_NAME} PUBLIC 
                       glad glfw imgui ${CORE_LIB_NAME})