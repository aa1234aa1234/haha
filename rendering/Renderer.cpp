//
// Created by sw_306 on 2025-09-22.
//

#include "Renderer.h"
#include <GLFW/glfw3.h>

void Renderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::clearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}