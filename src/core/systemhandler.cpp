#include "systemhandler.hpp"
#include "logger.hpp"
#include "window.hpp"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
    Include error module
*/


//Is it necessary?
SystemHandler::SystemHandler(){
    printf("[SYSTEM] Constructor\n");
}

SystemHandler::~SystemHandler(){
    printf("[SYSTEM] Destructor\n");
}


bool SystemHandler::Init(){
    //TODO

    m_Logger = &Logger::getLogger();

    m_Logger->log(INFO,"[GLFW] Initializing...");
    if( glfwInit() == false){

        m_Logger->log(ERROR,"[GLFW] Initalizing failed!");
        return false;
    }

    m_Logger->log(INFO,"[GLFW] Configuring profile...");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Logger->log(INFO,"[Window class] Creating");
    m_Logger->log(INFO,"[GLFW] Creating window...");
    m_Window = new Window();
    

    GLFWwindow* window = m_Window->GetWindowGLFW();
    if (window == nullptr)
    {
        m_Logger->log(ERROR,"[GLFW] Creating window failed!");
        return false;
    }

    glfwMakeContextCurrent(window);

    m_Logger->log(INFO,"[GLAD] Loading OpenGL functions...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        m_Logger->log(ERROR,"[GLAD] Loading OpenGL functions failed!");
        return false;
    }  

    return true;
}


void SystemHandler::Run(){

    GLFWwindow *window = m_Window->GetWindowGLFW();
    if(window == nullptr) return;


    while (!glfwWindowShouldClose(window))
    {
        // input

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void SystemHandler::Clean(){

    m_Logger->log(INFO,"[Window class] Deleting");
    if(m_Window != nullptr){
        delete m_Window;
        m_Window = nullptr;
    }
    
    m_Logger->log(INFO,"[GLFW] Terminating");
    glfwTerminate();

}