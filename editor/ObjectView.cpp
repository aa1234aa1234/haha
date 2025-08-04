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

void ObjectView::initSegmentTree(int nodeIdx, TreeNode* parent)
{
    static int idx = 0;
    SegmentTreeNode node{};
    node.start = nodeIdx;
    if (!nodeIdx) node.end = nodes.size()-1;
    else node.end = nodeIdx;
    for (int i = nodeIdx+1; i<nodes.size(); i++)
    {
        if (nodes[i]->parent != parent)
        {
            initSegmentTree(i, nodes[i]->parent);
        }
        else {
            node.end = i-1;
            break;
        }
    }
    segmentIndex[nodeIdx+1] = node;
}

int ObjectView::buildTree(int start, int end, int node) {
    if (start == end) {
        return segmentTree[node] = (nodes[start-1]->expanded ? nodes[start-1]->children.size() : 0);
    }
    int mid = (start+end)>>1;
    return segmentTree[node] = buildTree(start, mid, node*2) + buildTree(mid+1, end, node*2+1);
}

void ObjectView::updateTree(int start, int end, int node, int indexStart, int indexEnd, int diff) {
    if (start > end || end < indexStart || start > indexEnd) return;

    if (start == end) {
        segmentTree[node] = diff;
        return;
    }
    int mid = (start+end)>>1;
    updateTree(start, mid, node*2, indexStart, indexEnd, diff);
    updateTree(mid+1, end, node*2+1, indexStart, indexEnd, diff);
    segmentTree[node] = segmentTree[node*2] + segmentTree[node*2+1];
}

void ObjectView::init(SceneNode* root) {
    loadTree(root,this->root, STARTING_OFFSETX+position.x, STARTING_OFFSETY+position.y);

    for (auto& p : nodes)
    {
        p->textIndex = TextHandler::getInstance()->addText(p->position.x+tabWidth+1, p->position.y+2, p->text, 0.45);
    }
    segmentIndex.resize(nodes.size());
    segmentTree.reserve(nodes.size()*4);
    segmentIndex.push_back({0,0,0});
    initSegmentTree(0, this->root->parent);
    buildTree(1, nodes.size()-1, 1);
    updateTree(0);
}

void ObjectView::loadTree(SceneNode* sceneNode, TreeNode* node, int width, int height)
{
    node->text = sceneNode->getName();
    node->position = glm::vec2(width,height);
    node->icon.position = glm::vec2(width,height);
    node->icon.size = glm::vec2(tabWidth,rowHeight);
    nodes.reserve(nodes.size() + 1);
    nodes.emplace_back(node);

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

void ObjectView::updateTree(int idx)
{
    if (idx+1 >= nodes.size()) return;
    int cnt = 0;
    updateTree(1, nodes.size()-1, idx+1, segmentIndex[idx].start, segmentIndex[idx].end);
    std::cout << segmentTree[1] << std::endl;
    for (int i = idx+1; i<nodes.size(); i++)
    {
        if (nodes[i]->parent != nodes[idx]->parent)
        {
            if (nodes[i]->parent->expanded) cnt++;
            nodes[i]->visible = nodes[i]->parent->expanded & nodes[idx]->expanded;
            nodes[i]->icon.visible = nodes[i]->parent->expanded & nodes[idx]->expanded;
        }
        else
        {
            nodes[i]->position.y += cnt*rowHeight * (nodes[idx]->expanded ? 1 : -1);
            nodes[i]->icon.position.y += cnt*rowHeight * (nodes[idx]->expanded ? 1 : -1);
        }
    }
    numberofvisiblerows += cnt*(nodes[idx]->expanded ? 1 : -1);
    std::cout << selectedrow << "," << numberofvisiblerows << std::endl;
    if (selectedrow != -1 && selectedrow > idx)
    {
        selectedrow += cnt*(nodes[idx]->expanded ? 1 : -1);
        shader->use();
        glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), selectedrow);
    }
    if (selectedrow >= 0 && selectedrow < nodes.size() && !nodes[selectedrow+(numberofvisiblerows-1)]->visible)
    {
        selectedrow = -1;
        shader->use();
        glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), selectedrow);
    }
}

void ObjectView::render(Engine& engine) {
    shader->use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    for (auto& p : nodes) {
        if (!p->visible) { TextHandler::getInstance()->editText(p->position.x+tabWidth+1, p->position.y+2, "", p->textIndex, 0.45); }
        else TextHandler::getInstance()->editText(p->position.x+tabWidth+1, p->position.y+2, p->text, p->textIndex, 0.45);
        p->icon.render();
        if (p->textIndex == -1) p->textIndex = TextHandler::getInstance()->addText(p->position.x+tabWidth+1, p->position.y+2, p->text, 0.45);
    }
}

int ObjectView::onClick(glm::vec2 pos)
{
    for (int i = 0; i<nodes.size(); i++) {
        if (nodes[i]->icon.onClick(pos))
        {
            if (!nodes[i]->children.size()) return -1;
            nodes[i]->expanded = !nodes[i]->expanded;
            updateTree(i);
            return -1;
        }
    }
    selectedrow = (pos.y-STARTING_OFFSETY)/rowHeight;
    if (selectedrow >= nodes.size()) return -1;
    if (!nodes[selectedrow+(numberofvisiblerows-1)]->visible) return -1;
    //if (nodes[selectedrow]->icon.onClick(pos)) { nodes[selectedrow]->expanded = !nodes[selectedrow]->expanded; updateTree(selectedrow); return -1; }
    shader->use();
    glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), selectedrow);
    return -1;
}
