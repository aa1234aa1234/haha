//
// Created by D412 on 2025-07-16.
//

#include "ObjectView.h"

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
