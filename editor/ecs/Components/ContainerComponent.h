//
// Created by sw_303 on 2026-03-21.
//

#ifndef CONTAINERCOMPONENT_H
#define CONTAINERCOMPONENT_H
#include "Components.hpp"
#include "Entity.h"
#include "SystemCoordinator.h"

class ContainerComponent : public Entity
{
    SystemCoordinator* sc = nullptr;
public:
    ContainerComponent(EntityID componentId)
    {
        sc = SystemCoordinator::getInstance();
        Initialize(componentId);
    }

    void Initialize(EntityID componentId)
    {
        auto& transform = sc->GetComponent<TransformComponent>(componentId);
        sc->AddComponent(getId(), Container {componentId});
        sc->AddComponent(getId(), TransformComponent{transform.position, glm::vec4(30,30,30,1.0), transform.size});
        transform.position.y += 41;
        transform.size.y -= 42;
        transform.position.x += 1;
        transform.size.x -= 2;
    }
};

#endif //CONTAINERCOMPONENT_H
