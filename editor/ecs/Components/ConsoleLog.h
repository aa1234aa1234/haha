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
public:
    ConsoleLog(const glm::vec2& position, const glm::vec2& size) {
        Initialize(position,size);
    }

    void Initialize(glm::vec2 position, glm::vec2 size) {
        SystemCoordinator::getInstance()->RegisterEntity(this);
        SystemCoordinator::getInstance()->AddComponent(getId(), TransformComponent{position,glm::vec4(255,40,40,1), size});
    }
};

#endif //CONSOLELOG_H
