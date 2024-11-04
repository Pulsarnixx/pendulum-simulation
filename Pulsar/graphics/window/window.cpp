#include "window.hpp"

#include "glad.h"
#include <GLFW/glfw3.h>

#undef DEBUG

#ifdef DEBUG
    #include "../../../core/log/log.hpp"
#endif

/*
    CLASS WINDOW FUNTION
*/
Window::Window(){

    m_Window = glfwCreateWindow(DEFAULT_WEIGHT, DEFAULT_HEIGHT, DEFAULT_TITLE, NULL, NULL);
    m_Width  = DEFAULT_WEIGHT;
    m_Height = DEFAULT_HEIGHT;
    m_Title  = DEFAULT_TITLE;
}

Window::Window(unsigned int width, unsigned int height, const std::string& title){

    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    m_Width  = DEFAULT_WEIGHT;
    m_Height = DEFAULT_HEIGHT;
    m_Title  = title.c_str();

}


Window::~Window(){
    
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

void Window::SetVsync(bool option) const { glfwSwapInterval(option); } 

bool Window::ShouldWindowClose() const { return glfwWindowShouldClose(m_Window); }

void Window::onEvents() const {  glfwPollEvents(); }// glfwPollEvents should be for Event manager

void Window::onUpdate() const { glfwSwapBuffers(m_Window);} 

void Window::SetWindowDetails(unsigned int width, unsigned int height, const std::string& title){

    if(m_Window == nullptr) 
        return;

    glfwSetWindowSize(m_Window, width, height);
    glViewport(0,0,width,height);

    glfwSetWindowTitle(m_Window,title.c_str());
}

void Window::SetFrameBufferSizeCallBack(GLFWframebuffersizefun fun) const { glfwSetFramebufferSizeCallback(m_Window, fun); }
void Window::SetKeyCallBack(GLFWkeyfun fun) const {  glfwSetKeyCallback(m_Window,fun); }
void Window::SetCursorPostionCallBack(GLFWcursorposfun fun) const { glfwSetCursorPosCallback(m_Window, fun); }
void Window::SetScrollCallBack(GLFWscrollfun fun) const {  glfwSetScrollCallback(m_Window, fun); }

 


