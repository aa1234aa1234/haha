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
        if (frameBuffer) delete frameBuffer;
        if (offset != nullptr) delete offset;
    }

    void Initialize(glm::vec2 position, glm::vec2 size) {
        //frameBuffer = new FrameBuffer(Engine::getScreenWidth(), Engine::getScreenHeight());
        SystemCoordinator::getInstance()->RegisterEntity(this);
        SystemCoordinator::getInstance()->AddComponent(getId(), TransformComponent{position,size,glm::vec4(40,40,40,1)});
        SystemCoordinator::getInstance()->AddComponent(getId(), ScrollableComponent{0,0,0,0});
        offset = &SystemCoordinator::getInstance()->GetComponent<ScrollableComponent>(getId()).offset;
    }

    void update() override {
        std::cout << "offset: " << offset << std::endl;
    }

    void render(Engine& engine) override {

    }
};

#endif //ECSOBJECTVIEW_H
