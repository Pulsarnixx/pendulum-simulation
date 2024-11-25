add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(stb_image)
add_subdirectory(glm)
add_subdirectory(googletest)

# IMGUI configuration, cause repo doesnt have CMakefile and it is 
# submodule here
message(STATUS "[PULSARENGINE] Configuring IMGUI module...")
message(STATUS "[PULSARENGINE] ImGui include path: ${IMGUI_INCLUDE_DIR}")
message(STATUS "[PULSARENGINE] ImGui Backends include path: ${IMGUI_BACKENDS_INCLUDE_DIR}")
message(STATUS "[PULSARENGINE] ImPlot include path: ${IMPLOT_INCLUDE_DIR}")

set( IMGUI_SOURCES
     imgui/imgui.cpp imgui/imgui_demo.cpp
     imgui/imgui_draw.cpp  imgui/imgui_tables.cpp
     imgui/imgui_widgets.cpp
     implot/implot.cpp implot/implot_items.cpp
)

set( IMGUI_BACKENDS_SOURCES
     imgui/backends/imgui_impl_glfw.cpp 
     imgui/backends/imgui_impl_opengl3.cpp
)
    
set( IMGUI_HEADERS 
     imgui/imgui.h    imgui/imconfig.h
     imgui/imgui_internal.h imgui/imstb_rectpack.h
     imgui/imstb_textedit.h imgui/imstb_truetype.h
     implot/implot.h implot/implot_internal.h
)

set( IMGUI_BACKENDS_HEADERS 
     imgui/backends/imgui_impl_glfw.h
     imgui/backends/imgui_impl_opengl3.h
     imgui/backends/imgui_impl_opengl3_loader.h
)

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
        ${IMGUI_SOURCES} ${IMGUI_BACKENDS_SOURCES}
        ${IMGUI_HEADERS} ${IMGUI_BACKENDS_HEADERS})

target_include_directories( imgui PRIVATE 
                            ${IMGUI_INCLUDE_DIR} ${IMGUI_BACKENDS_INCLUDE_DIR} 
                            ${IMPLOT_INCLUDE_DIR} ${GLFW_INCLUDE_DIR}
                            )