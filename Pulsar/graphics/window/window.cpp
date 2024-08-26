#include "window.hpp"
#include <GLFW/glfw3.h>

#define DEFAULT_HEIGHT 1920
#define DEFAULT_WEIGHT 1090


#include <stdio.h>

Window::Window(){

    m_Window = glfwCreateWindow(DEFAULT_HEIGHT, DEFAULT_WEIGHT, "ExampleApp", NULL, NULL);
    m_Height = DEFAULT_HEIGHT;
    m_Width  = DEFAULT_WEIGHT;
}

Window::~Window(){
    
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_Window); }

void Window::onUpdate() const { glfwSwapBuffers(m_Window); glfwPollEvents();} // glfwPollEvents should be for Event manager


