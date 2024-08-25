#include "renderer.hpp"
#include "glad.h"

#include <stdio.h>

Renderer::Renderer(){
    printf("[RENDERER] Constructor\n");
};

Renderer::~Renderer(){
    printf("[RENDERER] Destructor\n");
};

void Renderer::OnRender() const{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}