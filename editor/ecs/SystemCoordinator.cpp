//
// Created by D412 on 2025-08-13.
//

#include "SystemCoordinator.h"

SystemCoordinator* SystemCoordinator::instance = 0;

void SystemCoordinator::RegisterEntity(Entity* entity)
{
    entityManager->addEntity(entity);
}