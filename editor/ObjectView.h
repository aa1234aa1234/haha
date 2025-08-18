//
// Created by D412 on 2025-07-16.
//

#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H
#define STARTING_OFFSETX 5
#define STARTING_OFFSETY 15
#include "UIComponent.h"
#include "SceneNode.h"
#include "Shader.h"
#include <vector>

#include "Icon.h"
#include <ExpandIcon.h>

#include "FrameBuffer.h"

class SceneNode;
class TreeRenderer;

struct TreeNode
{
    bool expanded = false, selected = false, visible = false;
    int textIndex = -1;
    std::string text;
    std::vector<TreeNode*> children;
    TreeNode* parent=nullptr;
    glm::vec2 position;
    ExpandIcon icon;
};

struct SegmentTreeNode
{
    int sum;
    int start,end;
};

class ObjectView : public UIComponent {
    int rowHeight = 20, tabWidth = 20;
    TreeNode* root;
    FrameBuffer* frameBuffer;
    std::vector<TreeNode*> nodes;
    std::vector<SegmentTreeNode> segmentIndex;
    std::vector<int> segmentTree;
    int selectedrow = -1, numberofvisiblerows = 1;

    // float ndc[24] = {
    //     1.0, 1.0, 0, 0,
    //     1.0,-1.0, 0, 0,
    //     -1.0,1.0, 0, 0,
    //     -1.0,-1.0, 0, 0,
    //     1.0,-1.0, 0, 0,
    //     -1.0,1.0, 0, 0
    // };
    float ndc[12] = {
        1.0, 1.0,
        1.0,-1.0,
        -1.0,1.0,
        -1.0,-1.0,
        1.0,-1.0,
        -1.0,1.0
    };

    unsigned int vao, vbo;
    Shader* shader = nullptr;
    const char* vertex = R"(
    #version 330 core

    layout(location = 0) in vec2 position;

    out vec2 pos;
    out vec2 texturepos;

    uniform mat4 projection;

    void main() {
        pos = position;
        if(pos.x == -1.0) pos.x = 0;
        if(pos.y == -1.0) pos.y = 0;
        gl_Position = projection * vec4(pos, 0.0, 1.0);
        texturepos = (vec2((projection * vec4(pos, 0.0, 1.0)).xy) + vec2(1.0,1.0))/2;
    }
    )";

    const char* frag = R"(
    #version 330 core

    layout (location = 0) out vec4 fragColor;

    in vec2 pos;
    in vec2 texturepos;

    uniform float selectedRow=-1.0;
    uniform float rowHeight;
    uniform float height;
    uniform sampler2D tex;

	vec4 NormalizeRGB(vec4 color) {
		return vec4(color.xyz/255.0,color.a);
	}

    void main() {
        //if(selectedRow != -1.0 && pos.y >= (1.0/height*rowCount*rowHeight*selectedRow)+(1.0/height*15) && pos.y <= (1.0/height*rowCount*rowHeight*selectedRow)+(1.0/height*15)+(1.0/height*rowHeight)) fragColor = NormalizeRGB(vec4(46,67,110,1.0));
        if(selectedRow != -1.0 && height-gl_FragCoord.y >= rowHeight*selectedRow+15 && height-gl_FragCoord.y <= rowHeight*(selectedRow+1)+15) fragColor = NormalizeRGB(vec4(46,67,110,1.0));
        else fragColor.a = 0.0;
        fragColor = texture(tex,vec2(texturepos.x,texturepos.y));
        //else fragColor = NormalizeRGB(vec4(46,67,110,1.0));
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
    void initSegmentTree(TreeNode* treeNode);
    int buildTree(int start, int end, int node);
    void updateTree(int start, int end, int node, int indexStart, int indexEnd, int diff);
    int sum(int start, int end, int node, int indexStart, int indexEnd);
    int getNodeIndex(int start, int end, int node, int idx);
public:
    ObjectView(const glm::vec2& pos, const glm::vec2& size);
    ~ObjectView()
    {
        if (frameBuffer) delete frameBuffer;
        destroy();
        destroyTree(root);
    }

    TreeNode* getRoot() { return root; }
    void init(SceneNode* root);
    void loadTree(SceneNode* sceneNode, TreeNode* node, int width, int height);
    void updateTree(int idx);
    void render(Engine& engine) override;
    int onClick(glm::vec2 pos) override;
};


#endif //OBJECTVIEW_H