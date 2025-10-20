//
// Created by sw_306 on 2025-10-01.
//

#include "VertexArray.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ErrorHandler.h"

VertexArray::VertexArray() {
    glCreateVertexArrays(1, &renderId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &renderId);
}

const void VertexArray::bind() {
    glBindVertexArray(renderId);
}

const void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer& vertexbuffer, VertexBufferLayout& layout) {
    bind();
    vertexbuffer.bind();
    auto& element = layout.getElements();
    int offset = 0;
    for (int i = 0; i < element.size(); i++) {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element[i].count, element[i].type, element[i].normalized, layout.getStride(), reinterpret_cast<const void*>(offset)));
        offset += sizeof(VertexBufferElement::getTypeSize(element[i].type)) * element[i].count;
    }
}

