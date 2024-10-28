#include "renderer.hpp"
#include "glad.h"

#include "core/Mesh.hpp"
#include "shader.hpp"

#include "../../core/log/log.hpp" //Logging


void Renderer::BeginRender() const {
    glClearColor(0.792f, 0.914f, 0.965f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Mesh& mesh, Shader& shaderProgram) const{

    GLsizei verticiesNumber = (GLsizei)mesh.GetVerticiesNumber();
    mesh.Bind();
    shaderProgram.Bind();
    
    //FOR VBO only
    glDrawArrays(GL_LINE_STRIP, 0, verticiesNumber);

}

void Renderer::RenderIndicies(Mesh& mesh, Shader& shaderProgram) const{

    GLsizei verticiesNumber = (GLsizei)mesh.GetVerticiesNumber();
    mesh.Bind();
    shaderProgram.Bind();
    //For VBO + EBO
    glDrawElements(GL_TRIANGLES, verticiesNumber, GL_UNSIGNED_INT, 0);
}

