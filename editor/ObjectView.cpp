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
    frameBuffer = new FrameBuffer(Engine::getScreenWidth(),Engine::getScreenHeight());
    this->uielement = {pos, glm::vec3(40, 40, 40), size, 121};
    shader->use();
    glUniform1f(glGetUniformLocation(shader->getId(), "rowHeight"), rowHeight);
    glUniform1f(glGetUniformLocation(shader->getId(),"height"), Engine::getScreenHeight());
    glm::mat4 mat = glm::ortho(0.0f, static_cast<float>(Engine::getScreenWidth()), static_cast<float>(Engine::getScreenHeight()), 0.0f);
    mat = glm::translate(mat, glm::vec3(pos, 0.0f));
    mat = glm::scale(mat, glm::vec3(size, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(mat));
}

void ObjectView::initSegmentTree(TreeNode* treeNode)
{
    static int idx = 0;
    int nodeidx = idx;
    SegmentTreeNode node{};
    node.start = idx++;
    for (auto& p : treeNode->children)
    {
        initSegmentTree(p);
    }
    node.end = idx-1;
    segmentIndex[nodeidx+1] = node;
}

int ObjectView::buildTree(int start, int end, int node) {
    if (start == end) {
        //return segmentTree[node] = (nodes[start-1]->expanded ? nodes[start-1]->children.size() : 0);
        return segmentTree[node] = 1;
    }
    int mid = (start+end)>>1;
    return segmentTree[node] = buildTree(start, mid, node*2) + buildTree(mid+1, end, node*2+1);
}

void ObjectView::updateTree(int start, int end, int node, int indexStart, int indexEnd, int diff) {
    if (start > end || end < indexStart || start > indexEnd) return;

    if (start == end) {
        segmentTree[node] += diff;
        return;
    }
    int mid = (start+end)>>1;
    updateTree(start, mid, node*2, indexStart, indexEnd, diff);
    updateTree(mid+1, end, node*2+1, indexStart, indexEnd, diff);
    segmentTree[node] = segmentTree[node*2] + segmentTree[node*2+1];
}

int ObjectView::sum(int start, int end, int node, int indexStart, int indexEnd)
{
    if (start > indexEnd || end < indexStart) return 0;
    if (indexStart <= start && indexEnd >= end) return segmentTree[node];
    int ans = 0;
    int mid = (start+end)>>1;
    ans += sum(start, mid, node*2, indexStart, indexEnd);
    ans += sum(mid+1, end, node*2+1, indexStart, indexEnd);
    return ans;
}

int ObjectView::getNodeIndex(int start, int end, int node, int idx)
{
    if (start == end) return start;
    int mid = (start+end)>>1;
    if (segmentTree[node*2] >= idx) return getNodeIndex(start, mid, node*2, idx);
    return getNodeIndex(mid+1, end, node*2+1, idx-segmentTree[node * 2]);
}


void ObjectView::init(SceneNode* root) {
    this->root->visible = true;
    loadTree(root,this->root, STARTING_OFFSETX+position.x, STARTING_OFFSETY+position.y);

    for (auto& p : nodes)
    {
        p->textIndex = TextHandler::getInstance()->addText(p->position.x+tabWidth+1, p->position.y+2, p->text, 0.45, frameBuffer->getFrameBuffer());
    }
    segmentIndex.resize(nodes.size());
    segmentTree.resize(nodes.size()*4);
    segmentIndex.push_back({0,0,0});
    initSegmentTree(this->root);
    buildTree(1, nodes.size()-1, 1);
    updateTree(0);

    frameBuffer->bind();
    glClearColor(40.0/255.0, 40.0/255.0, 40.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    frameBuffer->unbind();
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
    //updateTree(1, nodes.size()-1, idx+1, segmentIndex[idx].start, segmentIndex[idx].end, nodes[idx]->expanded ? -segmentTree[idx+1] : segmentTree[idx+1]);
    int sum1 = sum(1,nodes.size()-1, 1, segmentIndex[idx+1].start, segmentIndex[idx+1].end);
    for (int i = idx+1; i<idx+sum1; i++)
    {
        if (nodes[idx]->expanded)
        {
            if (!nodes[i]->parent->expanded)
            {
                i+=sum(1,nodes.size()-1,1,segmentIndex[i+1].start, segmentIndex[i+1].end);
            }
            if (nodes[i]->parent->expanded)
            {
                nodes[i]->visible = nodes[i]->parent->expanded & nodes[idx]->expanded;
                nodes[i]->icon.visible = nodes[i]->parent->expanded & nodes[idx]->expanded;
                cnt++;
            }
        }
        else
        {
            if (nodes[i]->visible)
            {
                nodes[i]->visible = false;
                nodes[i]->icon.visible = false;
                cnt++;
            }
        }
    }
    for (int i = idx+sum1; i<nodes.size(); i++)
    {
        nodes[i]->position.y += cnt*rowHeight * (nodes[idx]->expanded ? 1 : -1);
        nodes[i]->icon.position.y += cnt*rowHeight * (nodes[idx]->expanded ? 1 : -1);
    }
    std::cout << "cnt: " << cnt << std::endl;
    numberofvisiblerows += cnt*(nodes[idx]->expanded ? 1 : -1);
    std::cout << numberofvisiblerows << std::endl;
    if (selectedrow != -1 && selectedrow > idx)
    {
        shader->use();
        glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), (nodes[selectedrow]->position.y-STARTING_OFFSETY)/rowHeight);
    }
    if (selectedrow >= 0 && selectedrow < nodes.size() && !nodes[selectedrow]->visible)
    {
        selectedrow = -1;
        shader->use();
        glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), selectedrow);
    }
}

void ObjectView::render(Engine& engine) {

    shader->use();

    glBindTexture(GL_TEXTURE_2D, frameBuffer->getFrameTexture());
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    for (auto& p : nodes) {
        if (!p->visible) { TextHandler::getInstance()->editText(p->position.x+tabWidth+1, p->position.y+2, "", p->textIndex, 0.45, frameBuffer->getFrameBuffer()); }
        else TextHandler::getInstance()->editText(p->position.x+tabWidth+1, p->position.y+2, p->text, p->textIndex, 0.45, frameBuffer->getFrameBuffer());
        p->icon.render();
        if (p->textIndex == -1) p->textIndex = TextHandler::getInstance()->addText(p->position.x+tabWidth+1, p->position.y+2, p->text, 0.45, frameBuffer->getFrameBuffer());
    }
    frameBuffer->bind();
    glClearColor(40.0/255.0, 40.0/255.0, 40.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    frameBuffer->unbind();
}

int ObjectView::onClick(glm::vec2 pos)
{
    for (int i = 0; i<nodes.size(); i++) {
        if (!nodes[i]->visible) continue;
        if (nodes[i]->icon.onClick(pos))
        {
            if (!nodes[i]->children.size()) return -1;
            nodes[i]->expanded = !nodes[i]->expanded;
            updateTree(i);
            return -1;
        }
        if (nodes[i]->position.y <= pos.y && pos.y <= nodes[i]->position.y+rowHeight)
        {
            selectedrow = i;
            break;
        }
    }
    int selectedrowa = (pos.y-STARTING_OFFSETY)/rowHeight;
    std::cout << selectedrow << ' ' << getNodeIndex(1,nodes.size()-1, 1, selectedrowa+1) << std::endl;
    if (selectedrow >= nodes.size()) return -1;
    if (!nodes[selectedrow]->visible) return -1;
    //if (nodes[selectedrow]->icon.onClick(pos)) { nodes[selectedrow]->expanded = !nodes[selectedrow]->expanded; updateTree(selectedrow); return -1; }
    shader->use();
    glUniform1f(glGetUniformLocation(shader->getId(), "selectedRow"), selectedrowa);
    return -1;
}