#include "renderer.hpp"
#include "glad.h"

#include <stdio.h>

Renderer::Renderer(){
};

Renderer::~Renderer(){
};

void Renderer::OnRender() const{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}