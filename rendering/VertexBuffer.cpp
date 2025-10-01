//
// Created by sw_306 on 2025-10-01.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum usage) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &bufferId);
}

const void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

const void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::fill(const void *data, unsigned int size, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
