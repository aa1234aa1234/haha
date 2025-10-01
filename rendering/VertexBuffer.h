//
// Created by sw_306 on 2025-10-01.
//

#ifndef PROJECT_VERTEXBUFFER_H
#define PROJECT_VERTEXBUFFER_H
#include "header.h"

class VertexBuffer {
    unsigned int bufferId;
public:
    VertexBuffer(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();

    const void bind();
    const void unbind();

    void fill(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
};


#endif //PROJECT_VERTEXBUFFER_H