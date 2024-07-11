add_executable( ${PROJECT_NAME} main.cpp core/window.cpp 
                core/logger.cpp core/systemhandler.cpp)

include_directories(${GLAD_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} glad glfw)