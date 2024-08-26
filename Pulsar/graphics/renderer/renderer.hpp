#pragma once

/*
    Class represent 3D Renderer
*/
class Renderer{

public:
    //Constr, Destr.
    Renderer();
    ~Renderer();

    //Copy constr.
    Renderer(Renderer &) = delete;
    Renderer& operator = (const Renderer &) = delete;

    //Move constr.
    Renderer(Renderer &&) = delete;
    Renderer& operator = (Renderer &&) = delete;

    void OnRender() const;
  
private:

};