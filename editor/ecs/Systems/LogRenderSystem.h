//
// Created by user on 2026-04-15.
//

#ifndef LOGRENDERSYSTEM_H
#define LOGRENDERSYSTEM_H
#include "Components.hpp"
#include "System.h"
#include "SystemCoordinator.h"
#include "VertexBuffer.h"

class LogRenderSystem : public System {
    SystemCoordinator* sc;
    const int ROW_HEIGHT = 20;

public:
    LogRenderSystem() {}
    ~LogRenderSystem() {}

    void Initialize() {
        sc = SystemCoordinator::getInstance();
        Signature signature;
        signature.set(sc->GetComponentType<TransformComponent>(), true);
        signature.set(sc->GetComponentType<LogComponent>(), true);
        sc->SetSystemSignature<LogRenderSystem>(signature);
    }

    void Update() {

    }
};

#endif //LOGRENDERSYSTEM_H
