//
// Created by D412 on 2025-08-13.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.h"

class ComponentManager
{
    std::unordered_map<const char*, IComponentArray*> components;
    template<typename T>
    T* getComponentArray()
    {
        if (components.find(typeid(T).name()) == components.end()) return nullptr;
        return static_cast<T*>(components[typeid(T).name()]);
    }
public:
    ComponentManager() {}
    ~ComponentManager()
    {
        for (auto& p : components) delete p.second;
        components.clear();
    }

    template<typename T>
    T& getComponent(EntityID entity)
    {
        return getComponentArray<T>()->Get(entity);
    }

    template<typename T>
    void registerComponent()
    {
        components.insert({typeid(T).name, new T()});
    }

    template<typename T>
    void removeComponent(EntityID entity)
    {
        getComponentArray<T>()->Remove(entity);
    }

    template<typename T>
    void addComponent(EntityID entity, T component)
    {
        getComponentArray<T>()->Insert(entity,component);
    }
};

#endif //COMPONENTMANAGER_H
