#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h" 
#include "implot_internal.h"

/*
    Class represent graphical user interface
*/

//Forward dec.
class GLFWwindow;

class Gui{

public:
    //Constr, Destr.
    Gui() = default;
    ~Gui() = default;

    //Copy constr.
    Gui(Gui &) = delete;
    Gui& operator = (const Gui &) = delete;

    //Move constr.
    Gui(Gui &&) = delete;
    Gui& operator = (Gui &&) = delete;

    void OnBegin() const;
    void OnEnd() const;
  
private:

};