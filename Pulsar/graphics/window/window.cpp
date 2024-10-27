#include "window.hpp"

#include "glad.h"
#include <GLFW/glfw3.h>

#include "../../../core/log/log.hpp" //Logging 

/*
    GLFW CALL BACKS FUNTTIONS
*/

void FrameBufferCallBack(GLFWwindow* window, int width, int height){
    
    std::string s = "[FrameBuffer] resolution: " + std::to_string(width) + " x " + std::to_string(height);
    PX_CORE_TRACE(s);
    glViewport(0, 0, width, height);
    
}

void KeyInputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        PX_CORE_TRACE("[Keyboard] pressed: ESCAPE");
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        PX_CORE_TRACE("[Keyboard] pressed: W");
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        PX_CORE_TRACE("[Keyboard] pressed: S");
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        PX_CORE_TRACE("[Keyboard] pressed: D");
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        PX_CORE_TRACE("[Keyboard] pressed: A");
        
}

void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn){
    std::string s = "[Mouse] position: " + std::to_string(xposIn) + " " + std::to_string(yposIn);
    PX_CORE_TRACE(s);
}  

void ScrollCallBack(GLFWwindow* window, double xpos2, double ypos2){
    std::string s = "[Mouse Scroll] values: " + std::to_string(xpos2) + " " + std::to_string(ypos2);
    PX_CORE_TRACE(s);
}  


/*
    CLASS WINDOW FUNTION
*/
Window::Window(){

    m_Window = glfwCreateWindow(DEFAULT_WEIGHT, DEFAULT_HEIGHT, DEFAULT_TITLE, NULL, NULL);
    m_Width  = DEFAULT_WEIGHT;
    m_Height = DEFAULT_HEIGHT;
    m_Title  = DEFAULT_TITLE;

    setupGLFWCallBack();

}

Window::Window(unsigned int width, unsigned int height, const std::string& title){

    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    m_Width  = DEFAULT_WEIGHT;
    m_Height = DEFAULT_HEIGHT;
    m_Title  = title.c_str();

    setupGLFWCallBack();
}


Window::~Window(){
    
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

void Window::SetVsync(bool option) const { glfwSwapInterval(option); } 

bool Window::ShouldWindowClose() const { return glfwWindowShouldClose(m_Window); }

void Window::onEvents() const { glfwPollEvents(); }// glfwPollEvents should be for Event manager

void Window::onUpdate() const { glfwSwapBuffers(m_Window);} 

void Window::SetWindowDetails(unsigned int width, unsigned int height, const std::string& title){

    if(m_Window == nullptr) 
        return;

    glfwSetWindowSize(m_Window, width, height);
    glViewport(0,0,width,height);

    glfwSetWindowTitle(m_Window,title.c_str());
 }

void Window::setupGLFWCallBack(){

    glfwSetFramebufferSizeCallback(m_Window, FrameBufferCallBack);
    glfwSetKeyCallback(m_Window,KeyInputCallBack);
    glfwSetCursorPosCallback(m_Window, MouseCallBack);
    glfwSetScrollCallback(m_Window, ScrollCallBack);
}
 


