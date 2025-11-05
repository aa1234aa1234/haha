//
// Created by sw_306 on 2025-10-15.
//

#include "RenderingEngine.h"
#include "ErrorHandler.h"
#include "Engine.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "SkyBox.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"



RenderingEngine::RenderingEngine(Engine* engine) : engine(engine) {
    sceneCamera = engine->getSceneCamera();
    editorCamera = engine->getEditorCamera();
    mainShader = new Shader();
    mainShader->createFromSource("resources/shader/ambient.glsl");

    baseShader = new Shader();
    baseShader->createFromSource("resources/shader/base.glsl");
    skybox = new SkyBox(cubeMapFaces);
}

RenderingEngine::~RenderingEngine() {
    if (skybox) delete skybox;
    delete mainShader;
    delete baseShader;
}

void RenderingEngine::render(SceneNode* scenenode) {



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
    VertexArray vao;
    VertexBuffer vbo(skyboxVertices, 24 * 3 * sizeof(float), GL_STATIC_DRAW);
    IndexBuffer ibo(indices, 36);
    VertexBufferLayout layout;
    layout.push<float>(3);
    vao.addBuffer(vbo, layout);
    mainShader->use();
    mainShader->SetUniformMat4f("projection", sceneCamera->getProjectionMatrix());
    mainShader->SetUniformMat4f("view", sceneCamera->getViewMatrix());
    Renderer::getInstance()->draw(vao,ibo,*mainShader);


    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_EQUAL);
    skybox->render(sceneCamera->getProjectionMatrix(), sceneCamera->getViewMatrix());
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}