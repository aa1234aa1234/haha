//
// Created by sw_303 on 2025-08-30.
//

#ifndef UPDATESYSTEM_H
#define UPDATESYSTEM_H
#include "Components.hpp"
#include "SystemCoordinator.h"

class UpdateSystem : public System
{
public:
    UpdateSystem() {}
    ~UpdateSystem() {}

    void Initialize()
    {
        Signature signature;
        signature.set(SystemCoordinator::getInstance()->GetComponentType<DirtyComponent>(), true);
        SystemCoordinator::getInstance()->SetSystemSignature<UpdateSystem>(signature);
    }

    void Update()
    {
        auto it = entities.rbegin();
        for (; it != entities.rend(); )
        {
            SystemCoordinator::getInstance()->GetEntity(*it)->update();
            SystemCoordinator::getInstance()->RemoveComponent<DirtyComponent>(*it);
            std::cout << "updatesystem" << std::endl;
        }
    }
};

#endif //UPDATESYSTEM_H
