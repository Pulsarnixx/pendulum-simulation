#include "renderer.hpp"
#include "glad.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

void Renderer::BeginRender() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render() const{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

