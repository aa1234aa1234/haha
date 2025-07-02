//
// Created by sw_303 on 2025-06-21.
//

#include "SceneNode.h"

#include <algorithm>

SceneNode::SceneNode() : id(generateId()), parent(nullptr) {}

SceneNode::SceneNode(const std::string& name, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) : id(generateId()), parent(nullptr), transform(translation,rotation,scale) {}

SceneNode::SceneNode(const std::string& name) {}

SceneNode::~SceneNode()
{
    destroy();
}

void SceneNode::addSceneNode(SceneNode* node)
{
    children.reserve(children.size() + 1);
    children.emplace_back(node);
    node->setParent(this);
}

void SceneNode::removeSceneNode(SceneNode* node)
{
    children.erase(std::find(children.begin(), children.end(), node));
    delete node;
}

void SceneNode::addComponent(NodeComponent* component)
{
    components.reserve(components.size() + 1);
    components.emplace_back(component);
    component->setParent(this);
}

void SceneNode::removeComponent(NodeComponent* component)
{
    components.erase(std::find(components.begin(), components.end(), component));
    delete component;
}


void SceneNode::render(Shader* shader, Camera* camera)
{
    for (auto& p : children)
    {
        for (auto& k : p->getComponents())
        {
            k->render(shader,camera);
        }
    }
}

void SceneNode::update(float deltatime)
{
    for (auto& p : children)
    {
        p->update(deltatime);
    }
    for (auto& p : components)
    {
        p->update(deltatime);
    }
}
