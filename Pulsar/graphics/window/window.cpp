#include "window.hpp"

#include "glad.h"
#include <GLFW/glfw3.h>


#undef DEBUG

#ifdef DEBUG
    #include "../../../core/log/log.hpp"
#endif

/*
    GLFW CALL BACKS FUNTTIONS
*/
void FrameBufferCallBack(GLFWwindow* window, int width, int height){
    
    #ifdef DEBUG
        std::string s = "[FrameBuffer] resolution: " + std::to_string(width) + " x " + std::to_string(height);
        PX_CORE_TRACE(s);
    #endif
 
    glViewport(0, 0, width, height);    
}

void KeyInputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

    // float cameraStep = 2.5f * (1.0f / 60.0f);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){

        #ifdef DEBUG
            PX_CORE_TRACE("[Keyboard] pressed: ESCAPE");
        #endif
        
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }

    if (key == GLFW_KEY_W && action == GLFW_REPEAT){
        #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: W");
        #endif
        // camera.s_position += cameraStep * camera.s_front;
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT){
        #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: S");
        #endif
        // camera.s_position -= cameraStep * camera.s_front;
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT){
         #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: D");
        #endif
        // camera.s_position += cameraStep * glm::normalize(glm::cross(camera.s_front,camera.s_up));
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT){
        #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: A");
        #endif
        // camera.s_position -= cameraStep * glm::normalize(glm::cross(camera.s_front,camera.s_up));
    }

      
 
}

void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn){

    #ifdef DEBUG
        std::string s = "[Mouse] position: " + std::to_string(xposIn) + " " + std::to_string(yposIn);
        PX_CORE_TRACE(s);
    #endif

    // float xpos = static_cast<float>(xposIn);
    // float ypos = static_cast<float>(yposIn);

    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }

    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos;

    // lastX = xpos;
    // lastY = ypos;

    // const float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;

    // camera.yaw += xoffset;
    // camera.pitch += yoffset;

    // camera.yaw   += xoffset;
    // camera.pitch += yoffset;

    // if(camera.pitch > 89.0f)
    //     camera.pitch = 89.0f;
    // if(camera.pitch < -89.0f)
    //     camera.pitch = -89.0f;


    // glm::vec3 direction;
    // direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    // direction.y = sin(glm::radians(camera.pitch));
    // direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    // camera.s_front = glm::normalize(direction);
}  

void ScrollCallBack(GLFWwindow* window, double xpos2, double ypos2){

    #ifdef DEBUG
        std::string s = "[Mouse Scroll] values: " + std::to_string(xpos2) + " " + std::to_string(ypos2);
        PX_CORE_TRACE(s);
    #endif

    // camera.fov -= (float)ypos2;
    // if (camera.fov < 1.0f)
    //     camera.fov = 1.0f;
    // if (camera.fov > 90.0f)
    //     camera.fov = 90.0f; 

}  


/*
    CLASS WINDOW FUNTION
*/
Window::Window(){

    m_Window = glfwCreateWindow(DEFAULT_WEIGHT, DEFAULT_HEIGHT, DEFAULT_TITLE, NULL, NULL);
    m_Width  = DEFAULT_WEIGHT;
    m_Height = DEFAULT_HEIGHT;
    m_Title  = DEFAULT_TITLE;

    SetupCallBacks();

}

Window::Window(unsigned int width, unsigned int height, const std::string& title){

    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    m_Width  = DEFAULT_WEIGHT;
    m_Height = DEFAULT_HEIGHT;
    m_Title  = title.c_str();

    SetupCallBacks();
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

void Window::SetupCallBacks(){

    glfwSetFramebufferSizeCallback(m_Window, FrameBufferCallBack);
    glfwSetKeyCallback(m_Window,KeyInputCallBack);
    glfwSetCursorPosCallback(m_Window, MouseCallBack);
    glfwSetScrollCallback(m_Window, ScrollCallBack);
}
 


