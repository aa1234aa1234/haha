//
// Created by sw_306 on 2025-10-01.
//

#ifndef PROJECT_INDEXBUFFER_H
#define PROJECT_INDEXBUFFER_H


class IndexBuffer {
    unsigned int renderId;
    unsigned int count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    void fill(const void* data, unsigned int count);
};


#endif //PROJECT_INDEXBUFFER_H