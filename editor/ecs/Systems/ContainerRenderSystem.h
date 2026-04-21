//
// Created by user on 2026-03-26.
//

#ifndef CONTAINERRENDERSYSTEM_H
#define CONTAINERRENDERSYSTEM_H
#include <unordered_set>

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
    int w=0,h=0;
    VertexBuffer *vbo, *instancevbo;
    VertexArray* vao;

    struct TabData {
        glm::vec2 position;
        glm::vec2 size;
        bool isSelected = false;
    };

    std::vector<TabData> instanceData;

public:
    ContainerRenderSystem() : sc(SystemCoordinator::getInstance()), shader(nullptr), vbo(nullptr), instancevbo(nullptr), vao(nullptr) {}

    ~ContainerRenderSystem() {
        if (shader) delete shader;
        delete vao;
        delete vbo;
        delete instancevbo;
    }

    void Initialize(const int& width, const int& height) {
        shader = new Shader();
        shader->createFromSource("resources/shader/editor/container.glsl");

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
        sc->SetSystemSignature<ContainerRenderSystem>(signature);
    }

    void Update()
    {
        bool updateFlag=false;
        shader->use();
        glm::mat4 mat = glm::ortho(0.0f, static_cast<float>(this->w), static_cast<float>(this->h), 0.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
        for (auto& p : entities)
        {
            if (sc->EntityHasComponent<DirtyComponent>(p)) updateFlag = true;
            instanceData.push_back(TabData{});
        }
        if (updateFlag)
        {
            instancevbo->fill(instanceData.data(), instanceData.size() * sizeof(TabData), GL_STATIC_DRAW);
        }

        vao->bind();
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instanceData.size());

        //refactor when changing text rendering to batch rendering
        //make it so the log is already saved to a batch and only updates when a lines is added

        for (auto& p : entities)
        {
            ((ConsoleLog*)sc->GetEntity(p))->partitionLog();
        }

        instanceData.clear();
    }
};

#endif //CONTAINERRENDERSYSTEM_H
