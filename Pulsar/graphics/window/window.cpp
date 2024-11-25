#include "window.hpp"

#include <GLFW/glfw3.h> //glfw functions

#undef DEBUG

#ifdef DEBUG
    #include "../../../core/log/log.hpp"
#endif

/*
    TO DO:

    * create Event manager
    * extract  glfwPollEvents(); from Window class

*/

/*
    CLASS WINDOW FUNTION
// */

Window::Window(unsigned int width, unsigned int height, const std::string& title){

    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    m_Width  = width;
    m_Height = height;
    m_Title  = title.c_str();

}

Window::~Window(){
    
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

void Window::SetVsync(bool option) const { glfwSwapInterval(option); } 

bool Window::ShouldWindowClose() const { return glfwWindowShouldClose(m_Window); }

void Window::onEvents() const {  glfwPollEvents(); }

void Window::onUpdate() const { glfwSwapBuffers(m_Window); } 

//GLFW Call Backs
void Window::SetFrameBufferSizeCallBack(GLFWframebuffersizefun fun) const { glfwSetFramebufferSizeCallback(m_Window, fun); }
void Window::SetKeyCallBack(GLFWkeyfun fun) const {  glfwSetKeyCallback(m_Window,fun); }
void Window::SetCursorPostionCallBack(GLFWcursorposfun fun) const { glfwSetCursorPosCallback(m_Window, fun); }
void Window::SetScrollCallBack(GLFWscrollfun fun) const {  glfwSetScrollCallback(m_Window, fun); }

 


