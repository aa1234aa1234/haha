//
// Created by D412 on 2025-08-13.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>

#include "Entity.h"

class EntityManager
{
    std::vector<Entity*> entities;
    std::array<Signature, MAX_COMPONENTS> signatures;
public:
    ~EntityManager()
    {
        for (auto& p : entities) delete p;
        entities.clear();
    }

    void addEntity(Entity* entity)
    {
        entities.push_back(entity);
    }

    void setSignature(EntityID entity, Signature signature)
    {
        signatures[entity] = signature;
    }

    Signature getSignature(EntityID entity)
    {
        return signatures[entity];
    }

    Entity* getEntity(EntityID entity) {
        return entities[entity];
    }
};

#endif //ENTITYMANAGER_H
