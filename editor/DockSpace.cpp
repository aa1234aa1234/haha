//
// Created by sw_303 on 2025-06-21.
//

#include "DockSpace.h"
#include "Engine.h"

DockSpace::DockSpace()
{
    width = Engine::getScreenWidth(), height = Engine::getScreenHeight();
    frameBuffer = new FrameBuffer(width, height);
    shader = new Shader();
    shader->createFromSource(std::string(vertex), std::string(frag));
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenBuffers(1, &quadvbo);
    glGenVertexArrays(1, &quadvao);
    glBindVertexArray(quadvao);
    glBindBuffer(GL_ARRAY_BUFFER, quadvbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), ndc, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DockSpace::end()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(OverlayElement), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, buffer.size() * sizeof(OverlayElement), buffer.data());
    buffersize = buffer.size();
    buffer.clear();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DockSpace::render()
{
    shader->use();
    glBindVertexArray(vao);
    glLineWidth(3.0f);
    glDrawElements(GL_LINES, buffersize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(quadvao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DockSpace::update()
{

}

void DockSpace::resize()
{
    int width = Engine::getScreenWidth(), height = Engine::getScreenHeight();
    frameBuffer->resize(width, height);
}

