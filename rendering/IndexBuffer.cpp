//
// Created by sw_306 on 2025-10-01.
//

#include "IndexBuffer.h"
#include "header.h"
#include "ErrorHandler.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : count(count) {
    GLCall(glGenBuffers(1, &renderId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &renderId);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::fill(const void* data, unsigned int count) {
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data));
}

unsigned int IndexBuffer::getCount() const {
    return count;
}


