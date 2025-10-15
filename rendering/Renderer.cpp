//
// Created by sw_306 on 2025-09-22.
//

#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <GLFW/glfw3.h>

Renderer* Renderer::instance = 0;

void Renderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::clearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::draw(VertexArray& vao, IndexBuffer& index, Shader& shader, int instances) {
    shader.use();

    vao.bind();
    index.bind();
    if (instances > 1) {
        glDrawElementsInstanced(GL_TRIANGLES, index.getCount(), GL_UNSIGNED_INT, 0, instances);
    }
    else glDrawElements(GL_TRIANGLES, index.getCount(), GL_UNSIGNED_INT, nullptr);
}