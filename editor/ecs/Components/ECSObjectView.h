//
// Created by sw_306 on 2025-08-18.
//

#ifndef ECSOBJECTVIEW_H
#define ECSOBJECTVIEW_H
#include "Components.hpp"
#include "ScrollBar.h"
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
        ScrollBar* scrollbar = new ScrollBar();
        scrollbar->Initialize(position, size);
        SystemCoordinator::getInstance()->RegisterEntity(this);
        SystemCoordinator::getInstance()->AddComponent(getId(), TransformComponent{position,glm::vec4(255,255,255,1), size});
        SystemCoordinator::getInstance()->AddComponent(getId(), ScrollableComponent{0,0,0,0, scrollbar->getId()});
        offset = &SystemCoordinator::getInstance()->GetComponent<ScrollableComponent>(getId()).offset;
    }

    void update() override {
        *offset = 20;
        std::cout << "offset: " << *offset << std::endl;
    }
};

#endif //ECSOBJECTVIEW_H
