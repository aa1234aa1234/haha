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
        auto transform = sc->GetComponent<TransformComponent>(componentId);
        sc->AddComponent(getId(), ContainerComponent {componentId});
        sc->AddComponent(getId(), TransformComponent{glm::vec2(transform.position, transform.size, glm::vec3(40,40,40))});
    }
};

#endif //CONTAINERCOMPONENT_H
