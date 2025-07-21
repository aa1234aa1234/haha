//
// Created by D412 on 2025-07-16.
//

#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H
#include "UIComponent.h"
#include "SceneNode.h"
#include "Shader.h"
#include <vector>

#include "Icon.h"

class SceneNode;
class TreeRenderer;
class ExpandIcon;

struct TreeNode
{
    bool expanded = false, selected = false;
    int textIndex = -1;
    std::string text;
    std::vector<TreeNode*> children;
    TreeNode* parent=nullptr;
};

class ObjectView : public UIComponent {
    int rowHeight = 20;
    TreeNode root;
    void destroyTree(TreeNode* node)
    {
        for (auto it = node->children.begin(); it != node->children.end(); it++)
        {
            destroyTree(*it);
        }
        delete node;
    }
public:
    ObjectView(const glm::vec2& pos, const glm::vec2& size);
    ~ObjectView()
    {
        destroy();
        destroyTree(&root);
    }

    TreeNode& getRoot() { return root; }
    void loadTree(SceneNode* sceneNode, TreeNode* node);
    void render(Engine& engine) override;
    int onClick(glm::vec2 pos) override;
};

class TreeRenderer
{
    float ndc[12] = {
        1.0, 1.0,
        1.0,-1.0,
        -1.0,1.0,
        -1.0,-1.0,
        1.0,-1.0,
        -1.0,1.0,
        };
    unsigned int vao, vbo, quadvao, quadvbo;
    Shader* shader = nullptr;
    const char* vertex = R"(
    #version 330 core

    layout(location = 0) in vec2 position;
    layout(location = 1) in vec4 acolor;

    out vec2 pos;
    out vec4 colors;

    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
        colors = acolor;
        pos = position;
    }
    )";

    const char* frag = R"(
    #version 330 core

    layout (location = 0) out vec4 fragColor;

    in vec4 colors;
    in vec2 pos;

	vec4 NormalizeRGB(vec4 color) {
		return vec4(color.xyz/255.0,color.a);
	}

    void main() {
        if (colors.a != 0.0) fragColor = colors; else fragColor = vec4(1.0,1.0,1.0,0.0);
    }
    )";
public:
    TreeRenderer()
    {
        shader = new Shader();
        shader->createFromSource(vertex, frag);
    }
    ~TreeRenderer()
    {
        delete shader;
    }

    void render(TreeNode* root)
    {

    }
};

class ExpandIcon
{
    float ndc[12] = {
        1.0, 1.0,
        1.0,-1.0,
        -1.0,1.0,
        -1.0,-1.0,
        1.0,-1.0,
        -1.0,1.0,
    };
    glm::vec2 position;
    glm::vec2 size;
public:
    ExpandIcon()
    {
    }

    void render()
    {

    }
};



#endif //OBJECTVIEW_H
