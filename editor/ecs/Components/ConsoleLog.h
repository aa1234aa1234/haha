//
// Created by user on 2026-03-12.
//

#ifndef CONSOLELOG_H
#define CONSOLELOG_H
#include "Entity.h"
#include "SystemCoordinator.h"
#include "Components.hpp"
#include <glm/glm.hpp>

class ConsoleLog : public Entity {
    SystemCoordinator* sc;
public:
    ConsoleLog(const glm::vec2& position, const glm::vec2& size) {
        sc = SystemCoordinator::getInstance();
        Initialize(position,size);
    }

    void Initialize(glm::vec2 position, glm::vec2 size) {
        sc->RegisterEntity(this);
        sc->AddComponent(getId(), TransformComponent{position,glm::vec4(20,20,20,1), size});
        sc->AddComponent(getId(), ScrollableComponent{});
        sc->AddComponent(getId(), TitleComponent{"Console"});
    }
};

#endif //CONSOLELOG_H
