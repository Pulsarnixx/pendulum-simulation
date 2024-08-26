#Define all glad .h files
file(GLOB GLAD_INC
    ${GLAD_INCLUDE_DIR}/*.h
)

add_library(
        glad STATIC 
        src/glad.c  
        ${GLAD_INC})

target_include_directories(glad PRIVATE ${GLAD_INCLUDE_DIR})