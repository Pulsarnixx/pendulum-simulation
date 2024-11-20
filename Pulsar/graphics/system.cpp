#include "system.hpp"

//For using logger in this file
#include "log/log.hpp"

//For window managment
#include "glad.h"
#include "GLFW/glfw3.h"

//For gui managment
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//System instance
static System *s_Instance = nullptr;

//Flags
bool System::m_isGLFWInitialized = false;
bool System::m_isGLADInitilized  = false;
bool System:: m_isIMGUIInitialized = false;

//Data
Window* System::m_Window = nullptr;
Renderer* System::m_Renderer = nullptr;
Gui* System::m_Gui = nullptr;

#define PX_NATIVE_WINDOW_SYSTEM(platform) \
    ((platform == GLFW_PLATFORM_WIN32) ? "Win32" : \
    (platform == GLFW_PLATFORM_COCOA) ? "Cocoa" : \
    (platform == GLFW_PLATFORM_WAYLAND) ? "Wayland" : \
    (platform == GLFW_PLATFORM_X11) ? "X11" : "Unknown Platform")

System::System(){}
System::~System(){}

/*
    Functions that initialize all basic depedencies (GLFW, GLAD).
    For Windows and MacOS, glfw initlized theirs native window systems (WIN32, Cocoa)
    For Unix/Linux machines it choose X11 as default window system

    For rendering API it choose OpenGL context as default.

    Return: -
*/
void System::Init(){


    assert(!s_Instance);

    PX_CORE_TRACE("System initialization...");

    //Creating system instance after all success
    s_Instance = new System();
    PX_CORE_INFO("System initialization success!");
    
    //TODO: Change it for more adjustable maner
    #ifdef __linux__
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    #endif

    if( glfwInit() == false){
        
        PX_CORE_ERROR("GLFW initialization failed!");  //Change in the future...
        m_isGLFWInitialized = false;
        return;
    }

    m_isGLFWInitialized = true;
    PX_CORE_INFO("GLFW initialization success!");

    //OpenGL context for glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    CreateWindow(1600,900,"Application");

    if(m_Window == nullptr)
        ShutDown();
    
    GLFWwindow* currentWindow = m_Window->GetWindowGLFW();

    glfwMakeContextCurrent(currentWindow);

    //Load OpenGL context
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        PX_CORE_ERROR("GLAD initialization failed!");
        m_isGLADInitilized = false;
        ShutDown();
        return;
    }
    m_isGLADInitilized = true;
    PX_CORE_INFO("GLAD initialization success!");

    glViewport(0,0,1600,900);

    CreateRender();
    if(m_Renderer == nullptr)
        ShutDown();

    //Enable Depth test
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
    
    glEnable(GL_DEPTH_TEST);
  
    PrintPlatformDetails();
}

void System::InitUI(){

    assert(s_Instance);

    if(m_Window == nullptr || m_Renderer == nullptr){
        PX_CORE_ERROR("Initialize window and renderer first!");
        return;
    }

    // // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowGLFW(), true);
    ImGui_ImplOpenGL3_Init();

    m_isIMGUIInitialized = true;
    PX_CORE_INFO("IMGUI initialization success!");

    CreateGUI();
    if(m_Gui == nullptr)
        ShutDown();

}

void System::ShutDown(){

    assert(s_Instance);

    PX_CORE_TRACE("System terminating...");

    if(m_Gui != nullptr){
        delete m_Gui;
        m_Gui = nullptr;
        PX_CORE_INFO("Gui deletion success!");
    }

    if(m_isIMGUIInitialized == true){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        PX_CORE_INFO("IMGUI terminating success!");
    }

    if(m_Renderer != nullptr){
        delete m_Renderer;
        m_Renderer = nullptr;
        PX_CORE_INFO("Renderer deletion success!");
    }

    if(m_Window != nullptr){
        delete m_Window;
        m_Window = nullptr;
        PX_CORE_INFO("Window deletion success!");
    }

    if(m_isGLFWInitialized == true){
        glfwTerminate();
        PX_CORE_INFO("GLFW terminating success!");
    }

    if(s_Instance != nullptr){
        //Delete system instance
        delete s_Instance;
        s_Instance = nullptr;
        PX_CORE_INFO("System deletion success!");
    }
}


System& System::GetInstance(){

    if(s_Instance == nullptr)
        s_Instance = new System();

    return *s_Instance;
}


/*
    Function that print all information about initlized platform.
    Can be used only after system initialization.
*/
void System::PrintPlatformDetails(){

    assert(s_Instance);

    std::string base = "GLFW version: ";
    std::string suffix = glfwGetVersionString();
    PX_CORE_TRACE(base + suffix);

    base = "GLFW windowing system set: ";
    suffix = PX_NATIVE_WINDOW_SYSTEM(glfwGetPlatform());
    PX_CORE_TRACE(base + suffix);

    GLint major; GLint minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    base = "OpenGL version: ";
    suffix = std::to_string(major) + '.' + std::to_string(minor);
    PX_CORE_TRACE(base + suffix);

    base = "OpenGL version details: ";
    suffix = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    PX_CORE_TRACE(base + suffix);

    base = "OpenGL shading language version: ";
    suffix = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    PX_CORE_TRACE(base + suffix);

    base = "OpenGL vendor: ";
    suffix = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    PX_CORE_TRACE(base + suffix);

    base = "OpenGL renderer: ";
    suffix = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    PX_CORE_TRACE(base + suffix);
}

void System::CreateWindow(unsigned int width, unsigned int height, const std::string& title){

    //System didn't initialized
    assert(s_Instance);

    //Window had been created
    if(m_Window != nullptr){
        PX_CORE_WARN("Window had been created!");
        return;
    }

    //Window hadn't been created
    m_Window = new Window(width, height, title);
    if(m_Window == nullptr){
        PX_CORE_ERROR("Window creation failed!");
        return; 
    }

    PX_CORE_INFO("Window creation success!");
}

const Window* System::GetWindow(){

    //System didn't initialized
    assert(s_Instance);

    if(m_Window == nullptr){
        PX_CORE_WARN("You haven't created any window!");
        return nullptr;
    }

    return m_Window;
}

void System::CreateRender(){

    //System didn't initialized
    assert(s_Instance);

    //Window hadn't been created
    if(m_Window == nullptr){
        PX_CORE_WARN("You haven't created any window!");
        return;
    }

    //Renderer had been created
    if(m_Renderer != nullptr){
        PX_CORE_WARN("Render had been created!");
        return;
    }

    m_Renderer = new Renderer(); //In the future it will be different version of renderers (2D, 3D, GL, vulkan)
    if(m_Renderer == nullptr){
        PX_CORE_ERROR("Renderer creation failed!");
        return; 
    }

    //Update OpenGL context
    GLFWwindow* currentWindow = m_Window->GetWindowGLFW();
    glfwMakeContextCurrent(currentWindow);

    PX_CORE_INFO("Renderer creation success!");

}

const Renderer* System::GetRenderer(){

    //System didn't initialized
    assert(s_Instance);

    if(m_Renderer == nullptr){
        PX_CORE_WARN("You haven't created any renderer!");
        return nullptr;
    }

    return m_Renderer;
}

void System::CreateGUI(){

    //System didn't initialized
    assert(s_Instance);

    //Window hadn't been created
    if(m_Window == nullptr){
        PX_CORE_WARN("Create window first!");
        return;
    }

    if(m_Renderer == nullptr){
        PX_CORE_WARN("Create renderer first!");
        return;
    }

    //Gui had been created
    if(m_Gui != nullptr){
        PX_CORE_WARN("Gui had been created!");
        return;
    }

    m_Gui = new Gui(); 
    if(m_Gui == nullptr){
        PX_CORE_ERROR("Gui creation failed!");
        return; 
    }

    PX_CORE_INFO("Gui creation success!");
}

const Gui* System::GetGui(){

    //System didn't initialized
    assert(s_Instance);

    if(m_Gui == nullptr){
        PX_CORE_WARN("You haven't created gui!");
        return nullptr;
    }

    return m_Gui;
}

