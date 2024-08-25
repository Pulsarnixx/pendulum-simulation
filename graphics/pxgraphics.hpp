#pragma once

#include "window/window.hpp"
#include "renderer/renderer.hpp"
#include "widget/gui.hpp"

//typical singleton
class pxGraphicsManager {
    public:

        //Copy constr.
        pxGraphicsManager(const pxGraphicsManager&) = delete;
        pxGraphicsManager& operator=(const pxGraphicsManager&) = delete;

        //Move constr.
        pxGraphicsManager(pxGraphicsManager&&) = delete;
        pxGraphicsManager& operator=(pxGraphicsManager&&) = delete;

        //Access
        static pxGraphicsManager& getSystem() {
            static pxGraphicsManager system;
            return system;
        }

        //Utilities
        bool Init();
        void Clean();

        Window* GetWindow() const { return m_Window; }
        Renderer* GetRenderer() const { return m_Renderer; }
        Gui* GetGui() const { return m_Gui; }

    private:
        //Constr. & Destr.
        pxGraphicsManager();
        ~pxGraphicsManager();

    private:
        //what's graphics manages
        Window *m_Window = nullptr;
        Renderer *m_Renderer = nullptr;
        Gui *m_Gui = nullptr;

};