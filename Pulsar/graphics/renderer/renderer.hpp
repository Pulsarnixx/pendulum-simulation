#pragma once


//Forward dec.
class Mesh;
class Shader;

/*
    Class represent 3D Renderer
*/
class Renderer{

public:
    //Constr, Destr.
    Renderer() = default;
    ~Renderer() = default;

    //Copy constr.
    Renderer(Renderer &) = delete;
    Renderer& operator = (const Renderer &) = delete;

    //Move constr.
    Renderer(Renderer &&) = delete;
    Renderer& operator = (Renderer &&) = delete;


    void BeginRender() const;
    void RenderGrid(Shader& shaderProgram) const;
    void RenderMesh(Mesh& mesh, Shader& shaderProgram) const;
  
private:

};