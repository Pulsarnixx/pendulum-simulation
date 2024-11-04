#pragma once

#include "window/window.hpp"
#include "renderer/renderer.hpp"
#include "widget/gui.hpp"

//typical singleton
class System {
    public:

        //System configuration
        static void Init();
        static void InitUI();
        static void ShutDown();

        //System Access
        static System& GetInstance();
       
        //Window configuration
        static const Window* GetWindow();

        //Render configuration
        static const Renderer* GetRenderer();

        //Gui configuration
        static const Gui* GetGui();

        //Copy constr.
        System(const System&) = delete;
        System& operator=(const System&) = delete;

        //Move constr.
        System(System&&) = delete;
        System& operator=(System&&) = delete;

    private:
        //Constr. & Destr.
         System();
        ~System();

        //Utilities
        static void PrintPlatformDetails();

        //Creators, temporary private but in the future will be support to create multiple windows / renderers
        static void CreateWindow(unsigned int width, unsigned int height, const std::string& title);
        static void CreateRender();
        static void CreateGUI();

    private:

        static bool m_isGLFWInitialized;
        static bool m_isGLADInitilized;
        static bool m_isIMGUIInitialized;

        static Window* m_Window;
        static Renderer* m_Renderer;
        static Gui* m_Gui;
        //ResourceMangare *manager;
};



