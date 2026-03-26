//
// Created by user on 2026-03-26.
//

#ifndef CONTAINERRENDERSYSTEM_H
#define CONTAINERRENDERSYSTEM_H
#include "Components.hpp"
#include "Shader.h"
#include "System.h"
#include "SystemCoordinator.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class ContainerRenderSystem : public System {
    SystemCoordinator* sc;
    Shader* shader;
    int w,h;
    VertexBuffer* vbo;
    VertexArray* vao;

    struct TabData {
        glm::vec2 position;
        glm::vec2 size;
        bool isSelected = false;
    };
public:
    ContainerRenderSystem(const int& width, const int& height) {
        Initialize(width, height);
        shader = new Shader();
        shader->createFromSource("resources/shader/editor/container.glsl");
    }

    ~ContainerRenderSystem() {
        if (shader) delete shader;
        delete vao;
        delete vbo;
    }

    void Initialize(int& width, int& height) {
        w = width;
        h = height;

        vao = new VertexArray();

        vao->bind();
        //vbo = new VertexBuffer()

        Signature signature;
        signature.set(sc->GetComponentType<ContainerComponent>(), true);
        sc->SetSystemSignature<ContainerComponent>(signature);
    }
};

#endif //CONTAINERRENDERSYSTEM_H
