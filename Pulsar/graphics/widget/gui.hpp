#pragma once

/*
    Class represent graphical user interface
*/

//Forward dec.
class GLFWwindow;

class Gui{

public:
    //Constr, Destr.
    Gui(GLFWwindow* window);
    ~Gui();

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