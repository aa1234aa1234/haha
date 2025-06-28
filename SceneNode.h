//
// Created by sw_303 on 2025-06-21.
//

#ifndef SCENENODE_H
#define SCENENODE_H
#include <string>
#include <vector>
#include "NodeComponent.h"
#include "Shader.h"
#include "Transform.h"

using NodeID = uint64_t;


class Camera;
class Shader;
class Transform;
class NodeComponent;

class SceneNode {

    NodeID id=-1;
    SceneNode* parent;
    std::string name;
    std::vector<SceneNode*> children;
    std::vector<NodeComponent*> components;
    Transform transform;
protected:
    void destroy()
    {
        for (auto& p : children)
        {
            delete p;
        }
        children.clear();
        for (auto& p : components)
        {
            delete p;
        }
        components.clear();
    }
public:
    SceneNode();
    SceneNode(const std::string& name, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
    SceneNode(const std::string& name);
    virtual ~SceneNode();

    static NodeID generateId()
    {
        static NodeID id = 1;
        return id++;
    }

    template<class T>
    T* getComponent()
    {
        for (auto& p : components)
        {
            if (dynamic_cast<T*>(p)) { return static_cast<T*>(p); }
        }
        return nullptr;
    }

    NodeID getID() const { return id; }
    void setParent(SceneNode* node) { parent = node; }
    void addSceneNode(SceneNode* node);
    void removeSceneNode(SceneNode* node);
    void setName(const std::string& name) { this->name = name; }
    void render(Shader* shader, Camera* camera);
    void addComponent(NodeComponent* component);
    void removeComponent(NodeComponent* component);

    template<class T>
    void handleInput(T input)
    {
        for (auto& p : children)
        {
            p->handleInput(input);
        }
    }

    std::vector<NodeComponent*>& getComponents() { return components; }
    Transform& getTransform() { return this->transform; }
};



#endif //SCENENODE_H
