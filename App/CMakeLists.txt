set(APP_NAME exampleApp)

add_executable( ${APP_NAME} app.cpp )

target_include_directories( ${APP_NAME} PUBLIC 
                            ${PULSAR_INCLUDE_PATH}
                            )
target_link_libraries(${APP_NAME} PUBLIC ${PROJECT_NAME})