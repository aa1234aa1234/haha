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
#include <ExpandIcon.h>

class SceneNode;
class TreeRenderer;

struct TreeNode
{
    bool expanded = false, selected = false;
    int textIndex = -1;
    std::string text;
    std::vector<TreeNode*> children;
    TreeNode* parent=nullptr;
    glm::vec2 position;
    ExpandIcon icon;
};

class ObjectView : public UIComponent {
    int rowHeight = 20, tabWidth = 20;
    TreeNode* root;
    std::vector<TreeNode*> nodes;

    unsigned int vao, vbo;
    Shader* shader = nullptr;
    const char* vertex = R"(
    #version 330 core

    layout(location = 0) in vec2 position;
    layout(location = 1) in int expanded;

    out vec2 pos;
    flat out int big;

    uniform mat4 projection;

    void main() {
        gl_Position = projection * vec4(position, 0.0, 1.0);
        pos = position;
        big = expanded;
    }
    )";

    const char* frag = R"(
    #version 330 core

    layout (location = 0) out vec4 fragColor;

    in vec2 pos;
    flat in int big;

	vec4 NormalizeRGB(vec4 color) {
		return vec4(color.xyz/255.0,color.a);
	}

    void main() {
        //if (colors.a != 0.0) fragColor = colors; else fragColor = vec4(1.0,1.0,1.0,0.0);
    }
    )";

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
        destroyTree(root);
    }

    TreeNode* getRoot() { return root; }
    void init(SceneNode* root);
    void loadTree(SceneNode* sceneNode, TreeNode* node, int width, int height);
    void render(Engine& engine) override;
    int onClick(glm::vec2 pos) override;
};


#endif //OBJECTVIEW_H
