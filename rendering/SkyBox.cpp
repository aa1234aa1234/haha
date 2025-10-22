//
// Created by sw_306 on 2025-10-13.
//

#include "SkyBox.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

SkyBox::SkyBox(const std::vector<std::string> &faces) {
    texture = new Texture(faces);
    shader = new Shader();
    shader->createFromSource("resources/shader/cubemap.glsl");
    shader->use();
    shader->SetUniform1i("tex", 0);

    setUpBuffers();
}

SkyBox::~SkyBox() {
    delete texture;
    delete shader;
    delete vao;
    delete vbo;
    delete ibo;
}

void SkyBox::setUpBuffers() {
    float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
    };

    unsigned int indices[] = {
        // FRONT
        0, 1, 2,
        2, 3, 0,
        // BACK
        4, 5, 6,
        6, 7, 4,
        // UP
        8, 9, 10,
        10, 11, 8,
        // DOWN
        12, 13, 14,
        14, 15, 12,
        // LEFT
        16, 17, 18,
        18, 19, 16,
        // RIGHT
        20, 21, 22,
        22, 23, 20
    };


    vao = new VertexArray();
    vbo = new VertexBuffer(skyboxVertices, 24 * 3 * sizeof(float), GL_STATIC_DRAW);
    VertexBufferLayout layout;
    layout.push<float>(3);
    vao->addBuffer(*vbo, layout);
    ibo = new IndexBuffer(indices, 36);

}

void SkyBox::render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
    shader->use();

    glDepthFunc(GL_LEQUAL);
    shader->SetUniformMat4f("projection", projectionMatrix);
    shader->SetUniformMat4f("view", glm::mat4(glm::mat3(viewMatrix)));
    texture->bind();

    Renderer::getInstance()->draw(*vao,*ibo,*shader);

    vao->unbind();
    ibo->unbind();
    glDepthFunc(GL_LESS);
}
