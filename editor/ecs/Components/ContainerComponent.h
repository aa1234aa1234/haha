//
// Created by sw_303 on 2026-03-21.
//

#ifndef CONTAINERCOMPONENT_H
#define CONTAINERCOMPONENT_H
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
        sc->AddComponent(getId(), ContainerComponent {componentId});
    }
};

#endif //CONTAINERCOMPONENT_H
