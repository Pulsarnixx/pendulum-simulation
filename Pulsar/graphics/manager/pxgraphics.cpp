#include "pxgraphics.hpp"
#include "log/log.hpp"


#include <stdio.h>
#include "glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//Is it necessary?
pxGraphicsManager::pxGraphicsManager(){
    printf("[GRAPHICS] Constructor\n");
}

pxGraphicsManager::~pxGraphicsManager(){
    printf("[GRAPHICS] Destructor\n");
}


bool pxGraphicsManager::Init(){
    

    PX_CORE_INFO("GLFW init...");
    if( glfwInit() == false){
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    PX_CORE_INFO("Window creating...");
    m_Window = new Window();
    GLFWwindow* window = m_Window->GetWindowGLFW();
    if (window == nullptr){
        return false;
    }

    glfwMakeContextCurrent(window);

    PX_CORE_INFO("GLAD init...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return false;
    }

    PX_CORE_INFO("Render creating...");
    m_Renderer = new Renderer();
    if (m_Renderer == nullptr){
        return false;
    }

    PX_CORE_INFO("GUI creating...");
    m_Gui = new Gui(window);
    if (m_Gui == nullptr){
        return false;
    }

    return true;
}

void pxGraphicsManager::Clean(){

    PX_CORE_INFO("GUI deleting...");
    if(m_Gui != nullptr){
        delete m_Gui;
        m_Gui = nullptr;
    }

    PX_CORE_INFO("Render deleting...");
    if(m_Renderer != nullptr){
        delete m_Renderer;
        m_Renderer = nullptr;
    }

    PX_CORE_INFO("Window deleting...");
    if(m_Window != nullptr){
        delete m_Window;
        m_Window = nullptr;
    }
    
    glfwTerminate();
}