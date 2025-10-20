//
// Created by sw_306 on 2025-10-13.
//

#ifndef PROJECT_SKYBOX_H
#define PROJECT_SKYBOX_H
#include "header.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Texture;
class Shader;

class SkyBox {
    VertexArray* vao;
    VertexBuffer* vbo;
    IndexBuffer* ibo;
    Texture* texture;
    Shader* shader;

public:
    SkyBox(const std::vector<std::string> &faces);
    ~SkyBox();

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
    void setUpBuffers();
};


#endif //PROJECT_SKYBOX_H