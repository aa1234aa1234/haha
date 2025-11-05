//
// Created by sw_306 on 2025-10-01.
//

#ifndef PROJECT_VERTEXBUFFERLAYOUT_H
#define PROJECT_VERTEXBUFFERLAYOUT_H
#include "header.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getTypeSize(unsigned int type) {
        switch(type) {
            case GL_FLOAT:
            case GL_INT:
                return 4;
                break;
        }
    }
};

class VertexBufferLayout {

    int stride=0;
    std::vector<VertexBufferElement> elements;

public:
    VertexBufferLayout() {}
    ~VertexBufferLayout() {}

    template<typename T> void push(unsigned int count) {}

    std::vector<VertexBufferElement> getElements() const { return elements; }
    int getStride() const { return stride; }
};

template<> inline void VertexBufferLayout::push<float>(unsigned int count) {
    elements.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
    stride += count * sizeof(float);
}

template<> inline void VertexBufferLayout::push<int>(unsigned int count) {
    elements.push_back(VertexBufferElement{GL_INT, count, GL_FALSE});
    stride += count * sizeof(int);
}

#endif //PROJECT_VERTEXBUFFERLAYOUT_H