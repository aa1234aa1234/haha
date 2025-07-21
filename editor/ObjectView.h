//
// Created by D412 on 2025-07-16.
//

#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H
#include "UIComponent.h"
#include "SceneNode.h"
#include <vector>

class SceneNode;

class ObjectView : public UIComponent {
    struct TreeNode
    {
        bool expanded = false, selected = false;
        int textIndex = -1;
        std::string text;
        std::vector<TreeNode*> children;
        TreeNode* parent=nullptr;
    } root;

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

    void loadTree(SceneNode* sceneNode, TreeNode* node);
    void render(Engine& engine) override;
};



#endif //OBJECTVIEW_H
