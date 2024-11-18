#include "renderer.hpp"
#include "glad.h"

#include "core/Mesh.hpp"
#include "shader.hpp"


#define DEBUG
#ifdef DEBUG
    #include "../../core/log/log.hpp" //Logging
#endif

void Renderer::BeginRender() const {
    glClearColor(0.059f, 0.059f, 0.118f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderGrid(Shader& shaderProgram) const{

    shaderProgram.Bind();
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Renderer::RenderMesh(Mesh& mesh, Shader& shaderProgram) const{

    GLsizei verticiesNumber = (GLsizei)mesh.GetVerticiesNumber();
    mesh.Bind();
    shaderProgram.Bind();

    glDrawElements(GL_TRIANGLE_STRIP, verticiesNumber, GL_UNSIGNED_INT, 0);

}

void Renderer::RenderLine(Mesh& mesh, Shader& shaderProgram) const{

    GLsizei verticiesNumber = (GLsizei)mesh.GetVerticiesNumber();
    mesh.Bind();
    shaderProgram.Bind();

    glLineWidth(2.5f);
    glDrawArrays(GL_LINES, 0, verticiesNumber);

}

void Renderer::RenderCircle(Mesh& mesh, Shader& shaderProgram) const{

    GLsizei verticiesNumber = (GLsizei)mesh.GetVerticiesNumber();
    mesh.Bind();
    shaderProgram.Bind();


    glDrawArrays(GL_TRIANGLE_FAN, 0, verticiesNumber);

}


