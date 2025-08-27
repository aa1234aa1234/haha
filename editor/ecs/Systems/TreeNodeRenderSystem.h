//
// Created by sw_306 on 2025-08-25.
//

#ifndef PROJECT_TREENODERENDERSYSTEM_H
#define PROJECT_TREENODERENDERSYSTEM_H
#include "Components.hpp"
#include "ECSObjectView.h"
#include "SystemCoordinator.h"
#include "TextHandler.h"

class TreeNodeRenderSystem : public System{
    unsigned int vao,vbo,instancevbo;
    Shader* shader = nullptr;
    int width,height;

    struct Element {
        glm::vec2 position;
        glm::vec2 size;
        bool selected=false;
    };

public:
    TreeNodeRenderSystem() {}
    ~TreeNodeRenderSystem() {}

    void Initialize(int& width, int& height) {
        this->width = width;
        this->height = height;
        shader = new Shader("resources/shader/editor/treenodevert.glsl","resources/shader/editor/treenodefrag.glsl");

        float ndc[] = {
            1.0, 1.0 ,
            1.0,-1.0,
            -1.0,1.0,
            -1.0,-1.0,
            1.0,-1.0,
            -1.0,1.0,
        };
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &instancevbo);
        glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
        glBufferData(GL_ARRAY_BUFFER, MAX_COMPONENTS * sizeof(Element), NULL, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ndc), ndc, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribDivisor(1, 1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, size)));
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);

        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, selected)));
        glEnableVertexAttribArray(3);
        glVertexAttribDivisor(3, 1);


        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        Signature signature;
        signature.set(SystemCoordinator::getInstance()->GetComponentType<TreeNodeComponent>(), true);
        SystemCoordinator::getInstance()->SetSystemSignature<TreeNodeRenderSystem>(signature);
    }

    void Update(const EntityID treeView) {
        std::vector<Element> data;
        std::vector<Text> texts;
        glEnable(GL_SCISSOR_TEST);
        auto transform = SystemCoordinator::getInstance()->GetComponent<TransformComponent>(treeView);
        //glScissor(transform.position.x, height-transform.position.y, transform.size.x, transform.size.y);
        for (auto& p : entities) {
            auto treenode = SystemCoordinator::getInstance()->GetComponent<TreeNodeComponent>(p);
	        auto treeviewtransform = SystemCoordinator::getInstance()->GetComponent<TransformComponent>(treenode.treeView);
            if (!treenode.visible) continue;
            auto position = SystemCoordinator::getInstance()->GetComponent<PositionComponent>(p);
            std::string text = SystemCoordinator::getInstance()->GetComponent<TextComponent>(p).text;
            data.emplace_back(Element{position.position,glm::vec2(treeviewtransform.size.x, ROWHEIGHT),treenode.selected});
            texts.emplace_back(Text{position.position.x+TABWIDTH+1, position.position.y+2, text});
        }

        shader->use();
        glm::mat4 mat = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));

        glBindBuffer(GL_ARRAY_BUFFER, instancevbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(Element), data.data());

        glBindVertexArray(vao);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, data.size());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        for (auto& p : texts) {
            TextHandler::getInstance()->manualDrawText(p);
        }
        glDisable(GL_SCISSOR_TEST);
    }
};

#endif //PROJECT_TREENODERENDERSYSTEM_H
