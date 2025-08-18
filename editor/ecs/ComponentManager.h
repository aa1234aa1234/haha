//
// Created by D412 on 2025-08-13.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.h"

class ComponentManager
{
    std::unordered_map<const char*, IComponentArray*> components;
    std::unordered_map<const char*, uint32_t> componentTypes;
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
        static uint32_t componentType = 0;
        components.insert({typeid(T).name(), new T()});
        componentTypes.insert({typeid(T).name(), componentType});
        componentType++;
    }

    template<typename T>
    void removeComponent(EntityID entity)
    {
        getComponentArray<T>()->Remove(entity);
    }

    template<typename T>
    uint32_t getComponentType() {
        if (componentTypes.find(typeid(T).name()) == componentTypes.end()) { throw std::runtime_error("component type not found"); }
        return componentTypes[typeid(T).name()];
    }

    template<typename T>
    void addComponent(EntityID entity, T component)
    {
        getComponentArray<T>()->Insert(entity,component);
    }
};

#endif //COMPONENTMANAGER_H
