//
// Created by D412 on 2025-07-16.
//

#include "ObjectView.h"

#include "Engine.h"
#include "TextHandler.h"

ObjectView::ObjectView(const glm::vec2& pos, const glm::vec2& size) : UIComponent(pos, size) {
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), ndc, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    root = new TreeNode();
    shader = new Shader();
    shader->createFromSource(vertex,frag);
    this->uielement = {pos, glm::vec3(40, 40, 40), size, 121};
    shader->use();
    glUniform1f(glGetUniformLocation(shader->getId(), "rowHeight"), rowHeight);
    glUniform1f(glGetUniformLocation(shader->getId(),"height"), Engine::getScreenHeight());
    glm::mat4 mat = glm::ortho(0.0f, static_cast<float>(Engine::getScreenWidth()), static_cast<float>(Engine::getScreenHeight()), 0.0f);
    mat = glm::translate(mat, glm::vec3(pos, 0.0f));
    mat = glm::scale(mat, glm::vec3(size, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
}

void ObjectView::init(SceneNode* root) {
    loadTree(root,this->root, 5+position.x, 15+position.y);
    updateTree(0, this->root->expanded);
}

void ObjectView::loadTree(SceneNode* sceneNode, TreeNode* node, int width, int height)
{
    node->text = sceneNode->getName();
    node->position = glm::vec2(width,height);
    node->icon.position = glm::vec2(width,height);
    node->icon.size = glm::vec2(tabWidth,rowHeight);
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
        child->icon.size = glm::vec2(tabWidth,rowHeight);
        node->children.push_back(child);
        nodes.reserve(nodes.size() + 1);
        nodes.emplace_back(child);
    }
}

void ObjectView::updateTree(int idx, bool visibilty)
{
    if (idx+1 >= nodes.size()) return;
    for (int i = idx+1; i<nodes.size(); i++)
    {
        if (nodes[i]->parent != nodes[idx]->parent) nodes[i]->visible = visibilty;
    }
}

void ObjectView::render(Engine& engine) {
    shader->use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    for (auto& p : nodes) {
        if (!p->visible) continue;
        p->icon.render();
        if (p->textIndex == -1) p->textIndex = TextHandler::getInstance()->addText(p->position.x+tabWidth+1, p->position.y+2, p->text, 0.45);
        else if (!p->visible) { p->textIndex = TextHandler::getInstance()->removeText(p->textIndex);}
    }
}

int ObjectView::onClick(glm::vec2 pos)
{
    int selectedrow = 2;
    for (int i = 0; i<nodes.size(); i++) {
        if (nodes[i]->icon.onClick(pos)) { nodes[i]->expanded = !nodes[i]->expanded; updateTree(i,nodes[i]->expanded); return -1; }
    }
    shader->use();
    glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), selectedrow);
    return -1;
}
