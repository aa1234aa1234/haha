//
// Created by sw_306 on 2025-09-15.
//

#ifndef PROJECT_ECSSCENEVIEW_H
#define PROJECT_ECSSCENEVIEW_H
#include "Components.hpp"
#include "SystemCoordinator.h"

class ECSSceneView : public Entity{
public:
    ECSSceneView(unsigned int texture,glm::vec2 position, glm::vec2 size, glm::vec4 color) {
        Initialize(texture,position,size,color);
    }
    ~ECSSceneView() {}

    void Initialize(unsigned int texture,glm::vec2 position, glm::vec2 size, glm::vec4 color) {
        auto* sc = SystemCoordinator::getInstance();
        sc->RegisterEntity(this);
        sc->AddComponent(getId(), TextureComponent{texture});
        sc->AddComponent(getId(), TransformComponent{position, color, size});
    }

};

#endif //PROJECT_ECSSCENEVIEW_H