//
// Created by sw_306 on 2025-09-22.
//

#ifndef PROJECT_HANDLEINPUTSYSTEM_H
#define PROJECT_HANDLEINPUTSYSTEM_H
#include "Components.hpp"
#include "SystemCoordinator.h"

class HandleInputSystem : public System {
public:
    HandleInputSystem() {}
    ~HandleInputSystem() {}

    void Initialize() {
        auto* sc = SystemCoordinator::getInstance();
        Signature signature;
        signature.set(sc->GetComponentType<HandleInput>(), true);
        sc->SetSystemSignature<HandleInputSystem>(signature);
    }

    void Update(float deltatime) {
        if (Input::getInstance()->getEventType() == -1) return;
        for (auto& p : entities) {
            SystemCoordinator::getInstance()->GetEntity(p)->update(deltatime);
        }
    }
};

#endif //PROJECT_HANDLEINPUTSYSTEM_H