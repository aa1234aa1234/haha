//
// Created by D412 on 2025-07-16.
//

#include "ObjectView.h"

#include "TextHandler.h"

ObjectView::ObjectView(const glm::vec2& pos, const glm::vec2& size) : UIComponent(pos, size) {
    root = new TreeNode();
    shader = new Shader();
    shader->createFromSource(vertex,frag);
    this->uielement = {pos, glm::vec3(40, 40, 40), size, 121};
}

void ObjectView::init(SceneNode* root) {
    loadTree(root,this->root, 5+position.x, 15+position.y);
}

void ObjectView::loadTree(SceneNode* sceneNode, TreeNode* node, int width, int height)
{
    node->text = sceneNode->getName();
    node->position = glm::vec2(width,height);
    nodes.reserve(nodes.size() + 1);
    nodes.emplace_back(node);
    if (!node->children.size()) {
        node->icon.visible = false;
    }
    for (int i = 0; i<sceneNode->getChildren().size(); i++)
    {
        TreeNode* child = new TreeNode();
        child->parent = node;

        loadTree(sceneNode->getChildren()[i], child, width+tabWidth, height+rowHeight*(i+1));
        node->children.push_back(child);
    }
    for (int i = 0; i<sceneNode->getComponents().size(); i++)
    {
        TreeNode* child = new TreeNode();
        child->parent = node;
        child->text = "this is a work in progress";
        child->position = glm::vec2(width+tabWidth,height+rowHeight*(i+1));
        child->icon.position = glm::vec2(width+tabWidth,height+rowHeight*(i+1));
        child->icon.size = glm::vec2(tabWidth,rowHeight*(i+1));
        node->children.push_back(child);
        nodes.reserve(nodes.size() + 1);
        nodes.emplace_back(child);
    }
}

void ObjectView::render(Engine& engine) {
    shader->use();
    for (auto& p : nodes) {
        p->icon.render();
        if (p->textIndex == -1) p->textIndex = TextHandler::getInstance()->addText(p->position.x+tabWidth+1, p->position.y, p->text, 0.45);
    }
}

int ObjectView::onClick(glm::vec2 pos)
{
    for (auto& p : nodes) {
        if (p->icon.onClick(pos)) { p->expanded = !p->expanded; return -1; }
    }

    return -1;
}
