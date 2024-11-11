set(APP_NAME PrototypeApp)

add_executable( ${APP_NAME} app.cpp simulation2D.cpp simulation3D.cpp)

target_include_directories( ${APP_NAME} PUBLIC 
                            ${PULSAR_INCLUDE_PATH}
                            )
target_link_libraries(${APP_NAME} PUBLIC ${PROJECT_NAME})

set_target_properties( ${APP_NAME} PROPERTIES 
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/App/"
                     )