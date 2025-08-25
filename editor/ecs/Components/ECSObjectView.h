//
// Created by sw_306 on 2025-08-18.
//

#ifndef ECSOBJECTVIEW_H
#define ECSOBJECTVIEW_H
#define STARTING_OFFSETX 5
#define STARTING_OFFSETY 15
#include "Components.hpp"
#include "ScrollBar.h"
#include "SystemCoordinator.h"

class ECSObjectView : public Entity {
    int rowHeight=20, rowWidth=20;
    FrameBuffer* frameBuffer;
    int* offset;
    EntityID rootNode;
public:
    ECSObjectView(glm::vec2 position, glm::vec2 size) {
        Initialize(position, size);
    }

    ~ECSObjectView() {
        if (frameBuffer) delete frameBuffer;
        if (offset != nullptr) delete offset;
    }

    void Initialize(glm::vec2 position, glm::vec2 size) {
        ScrollBar* scrollbar = new ScrollBar();
        scrollbar->Initialize(position, size);
        SystemCoordinator::getInstance()->RegisterEntity(this);
        SystemCoordinator::getInstance()->AddComponent(getId(), TransformComponent{position,glm::vec4(255,255,255,1), size});
        SystemCoordinator::getInstance()->AddComponent(getId(), ScrollableComponent{0,0,0,0, scrollbar->getId()});
        offset = &SystemCoordinator::getInstance()->GetComponent<ScrollableComponent>(getId()).offset;

        rootNode = CreateTreeNode();
    }

    void loadTree(SceneNode* sceneNode, EntityID node, int width, int height) {
        SystemCoordinator::getInstance()->GetComponent<TextComponent>(node).text = sceneNode->getName();
        SystemCoordinator::getInstance()->GetComponent<PositionComponent>(node).position = glm::vec2(width,height);
    }

    int CreateTreeNode() {
        EntityID id = SystemCoordinator::getInstance()->CreateEntity();
        SystemCoordinator::getInstance()->AddComponent(id, TextComponent{});
        SystemCoordinator::getInstance()->AddComponent(id, PositionComponent{});
        SystemCoordinator::getInstance()->AddComponent(id, TreeNodeComponent{});
        SystemCoordinator::getInstance()->AddComponent(id, ContentComponent{});
        return id;
    }

    void update() override {
        *offset = 20;
        std::cout << "offset: " << *offset << std::endl;
    }
};

#endif //ECSOBJECTVIEW_H
