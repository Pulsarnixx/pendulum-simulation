set(APP_NAME Simulation)

#Shaders and test folder path
set(CIRCLE_SHADER "${CMAKE_SOURCE_DIR}/res/shaders/circle.shader")
add_compile_definitions(CIRCLE_SHADER="${CIRCLE_SHADER}")

set(LINE_SHADER "${CMAKE_SOURCE_DIR}/res/shaders/line.shader")
add_compile_definitions(LINE_SHADER="${LINE_SHADER}")

set(TRAIL_SHADER "${CMAKE_SOURCE_DIR}/res/shaders/trail.shader")
add_compile_definitions(TRAIL_SHADER="${TRAIL_SHADER}")

set(TEST_FOLDER_PATH "${CMAKE_SOURCE_DIR}/tests_results/")
add_compile_definitions(TEST_FOLDER_PATH="${TEST_FOLDER_PATH}")

add_executable( ${APP_NAME} app.cpp simulation2D.cpp pendulum.cpp numerical_eq.cpp)

target_include_directories( ${APP_NAME} PUBLIC 
                            ${PULSAR_INCLUDE_PATH}
                            )
target_link_libraries(${APP_NAME} PUBLIC ${PROJECT_NAME})

set_target_properties( ${APP_NAME} PROPERTIES 
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/App/"
                     )