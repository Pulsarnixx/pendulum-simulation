#include "window.hpp"
#include <GLFW/glfw3.h>

#define DEFAULT_HEIGHT 1200
#define DEFAULT_WEIGHT 600


Window::Window(){

    m_Window = glfwCreateWindow(DEFAULT_HEIGHT, DEFAULT_WEIGHT, "pulsarEngine", NULL, NULL);
    m_Height = DEFAULT_HEIGHT;
    m_Width  = DEFAULT_WEIGHT;
}

Window::~Window(){
    
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

