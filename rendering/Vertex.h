//
// Created by sw_306 on 2025-10-01.
//

#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H
#include "VertexBufferLayout.h"

struct VertexP {
    glm::vec3 position;
    static VertexBufferLayout getLayout() {
        VertexBufferLayout layout;
        layout.push<float>(3);
        return layout;
    }
};

struct VertexPUV {
    glm::vec3 position;
    glm::vec2 texCoord;
    static VertexBufferLayout getLayout() {
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(2);
        return layout;
    }
};

struct VertexPN {
    glm::vec3 position;
    glm::vec3 normal;
    static VertexBufferLayout getLayout() {
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        return layout;
    }
};

struct VertexPNUV {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    static VertexBufferLayout getLayout() {
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        layout.push<float>(2);
        return layout;
    }
};

struct VertexPNCUV {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 texCoord;
    static VertexBufferLayout getLayout() {
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        layout.push<float>(4);
        layout.push<float>(2);
        return layout;
    }
};

#endif //PROJECT_VERTEX_H