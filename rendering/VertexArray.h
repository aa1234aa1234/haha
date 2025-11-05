//
// Created by sw_306 on 2025-10-01.
//

#ifndef PROJECT_VERTEXARRAY_H
#define PROJECT_VERTEXARRAY_H
#include "header.h"

class VertexBufferLayout;
class VertexBuffer;

class VertexArray {
    unsigned int renderId;
public:
    VertexArray();
    ~VertexArray();

    const void bind();
    const void unbind();
    void addBuffer(VertexBuffer& vertexbuffer, const VertexBufferLayout& layout);
};


#endif //PROJECT_VERTEXARRAY_H