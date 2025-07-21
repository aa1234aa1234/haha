//
// Created by D412 on 2025-07-16.
//

#include "ObjectView.h"

ObjectView::ObjectView(const glm::vec2& pos, const glm::vec2& size) : UIComponent(pos,size) {
    this->uielement = {pos,glm::vec3(40,40,40), size, 121};
}

void ObjectView::loadTree(SceneNode* sceneNode, TreeNode* node)
{
    node->text = sceneNode->getName();
    for (auto& p : sceneNode->getChildren())
    {
        TreeNode* child = new TreeNode();
        child->parent = node;
        loadTree(p, child);
        node->children.push_back(child);
    }
    for (auto& p : sceneNode->getComponents())
    {
        TreeNode* child = new TreeNode();
        child->parent = node;
        child->text = "this is a work in progress";
        node->children.push_back(child);
    }
}

void ObjectView::render(Engine& engine) {

}

int ObjectView::onClick(glm::vec2 pos)
{
    return -1;
}
