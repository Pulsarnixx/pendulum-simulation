add_executable( ${PROJECT_NAME} app.cpp )

target_include_directories( ${PROJECT_NAME} PUBLIC 
                            ${CORE_INCLUDE_PATH} ${GRAPHICS_INCLUDE_PATH}
                            )
target_link_libraries(${PROJECT_NAME} pxcore pxgraphics)