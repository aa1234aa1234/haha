//
// Created by D412 on 2025-08-13.
//

#ifndef SYSTEMCOORDINATOR_H
#define SYSTEMCOORDINATOR_H
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"


class SystemCoordinator {
    static SystemCoordinator* instance;
    SystemManager* systemManager;
    EntityManager* entityManager;
    ComponentManager* componentManager;

    void init()
    {
        systemManager = new SystemManager();
        entityManager = new EntityManager();
        componentManager = new ComponentManager();
    }
    void destroy()
    {
        delete systemManager;
        delete entityManager;
        delete componentManager;
    }
public:
    SystemCoordinator() { init(); }
    ~SystemCoordinator() { destroy(); }

    static SystemCoordinator* getInstance()
    {
        if (!instance) instance = new SystemCoordinator();
        return instance;
    }

    static void destroyInstance()
    {
        if (instance) delete instance;
    }

    void RegisterEntity(Entity* entity);
};



#endif //SYSTEMCOORDINATOR_H
