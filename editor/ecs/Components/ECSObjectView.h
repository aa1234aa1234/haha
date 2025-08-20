//
// Created by sw_306 on 2025-08-18.
//

#ifndef ECSOBJECTVIEW_H
#define ECSOBJECTVIEW_H
#include "Components.hpp"
#include "SystemCoordinator.h"

class ECSObjectView : public Entity {
    FrameBuffer* frameBuffer;
    int* offset;
public:
    ECSObjectView(glm::vec2 position, glm::vec2 size) {
        Initialize(position, size);
    }

    ~ECSObjectView() {
        delete frameBuffer;
    }

    void Initialize(glm::vec2 position, glm::vec2 size) {
        frameBuffer = new FrameBuffer(Engine::getScreenWidth(), Engine::getScreenHeight());
        SystemCoordinator::getInstance()->RegisterEntity(this);
        SystemCoordinator::getInstance()->AddComponent(getId(), TransformComponent{position,size,glm::vec4(40,40,40,1)});
        SystemCoordinator::getInstance()->AddComponent(getId(), ScrollableComponent{0,0,0,0});
    }

    void update() override {

    }

    void render(Engine& engine) override {

    }
};

#endif //ECSOBJECTVIEW_H
