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
#include "VertexBufferLayout.h"

class ContainerRenderSystem : public System {
    SystemCoordinator* sc;
    Shader* shader;
    int w,h;
    VertexBuffer *vbo, *instancevbo;
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
        delete instancevbo;
    }

    void Initialize(int& width, int& height) {
        float ndc[] = {
            1.0, 1.0 ,
            1.0,-1.0,
            -1.0,1.0,
            -1.0,-1.0,
            1.0,-1.0,
            -1.0,1.0,
        };

        w = width;
        h = height;

        vao = new VertexArray();

        vao->bind();
        VertexBufferLayout layout, layout2;
        layout.push<float>(2);
        layout.push<float>(2);
        layout.push<float>(1);
        layout2.push<float>(2);
        vbo = new VertexBuffer(ndc, sizeof(ndc), GL_STATIC_DRAW);
        instancevbo = new VertexBuffer(NULL, sizeof(TabData) * 1000, GL_STATIC_DRAW);
        vao->addBuffer(*vbo, layout2);
        vao->addBuffer(*instancevbo, layout);
        vao->unbind();

        Signature signature;
        signature.set(sc->GetComponentType<Container>(), true);
        signature.set(sc->GetComponentType<TransformComponent>(), true);
        sc->SetSystemSignature<Container>(signature);
    }
};

#endif //CONTAINERRENDERSYSTEM_H
