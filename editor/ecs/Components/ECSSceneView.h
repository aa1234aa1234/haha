//
// Created by sw_306 on 2025-09-15.
//

#ifndef PROJECT_ECSSCENEVIEW_H
#define PROJECT_ECSSCENEVIEW_H
#include "Components.hpp"
#include "SystemCoordinator.h"

class ECSSceneView : public Entity{
public:
    ECSSceneView() {}
    ~ECSSceneView() {}

    void Initialize(unsigned int texture) {
        auto* sc = SystemCoordinator::getInstance();
        sc->RegisterEntity(this);
        sc->AddComponent(getId(), TextureComponent{texture});
    }
};

#endif //PROJECT_ECSSCENEVIEW_H