//
// Created by sw_306 on 2025-08-18.
//

#ifndef ECSOBJECTVIEW_H
#define ECSOBJECTVIEW_H
#define STARTING_OFFSETX 5
#define STARTING_OFFSETY 15
#define ROWHEIGHT 20
#define TABWIDTH 20
#include "Components.hpp"
#include "ScrollBar.h"
#include "SystemCoordinator.h"
#include "Application.h"

struct ECSSegmentTreeNode
{
    int sum;
    int start,end;
};

class ECSObjectView : public Entity {
    int rowHeight=20, tabWidth=20;
    std::vector<ECSSegmentTreeNode> segmentIndex;
    std::vector<int> segmentTree;
    FrameBuffer* frameBuffer;
    int* offset;
    EntityID rootNode;

    void initSegmentTree(EntityID treeNode) {
        static int idx = 0;
        int nodeidx = idx;
        ECSSegmentTreeNode node{};
        node.start = idx++;
        for (auto& p : SystemCoordinator::getInstance()->GetComponent<ContentComponent>(treeNode).entities)
        {
            initSegmentTree(p);
        }
        node.end = idx-1;
        segmentIndex[nodeidx+1] = node;
    }

    int buildTree(int start, int end, int node) {
        if (start == end) {
            //return segmentTree[node] = (nodes[start-1]->expanded ? nodes[start-1]->children.size() : 0);
            return segmentTree[node] = 1;
        }
        int mid = (start+end)>>1;
        return segmentTree[node] = buildTree(start, mid, node*2) + buildTree(mid+1, end, node*2+1);
    }

    void updateTree(int start, int end, int node, int indexStart, int indexEnd, int diff) {
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

    int sum(int start, int end, int node, int indexStart, int indexEnd) {
        if (start > indexEnd || end < indexStart) return 0;
        if (indexStart <= start && indexEnd >= end) return segmentTree[node];
        int ans = 0;
        int mid = (start+end)>>1;
        ans += sum(start, mid, node*2, indexStart, indexEnd);
        ans += sum(mid+1, end, node*2+1, indexStart, indexEnd);
        return ans;
    }
public:
    ECSObjectView(glm::vec2 position, glm::vec2 size, Application* app) {
        Initialize(position, size, app);

    }

    ~ECSObjectView() {
        if (frameBuffer) delete frameBuffer;
        if (offset != nullptr) delete offset;
    }

    void Initialize(glm::vec2 position, glm::vec2 size, Application* app) {
        ScrollBar* scrollbar = new ScrollBar();
        scrollbar->Initialize(position, size);
        SystemCoordinator::getInstance()->RegisterEntity(this);
        SystemCoordinator::getInstance()->AddComponent(getId(), TransformComponent{position,glm::vec4(255,255,255,1), size});
        SystemCoordinator::getInstance()->AddComponent(getId(), ScrollableComponent{0,0,0,0, scrollbar->getId()});
        SystemCoordinator::getInstance()->AddComponent(getId(), ContentComponent{});

        offset = &SystemCoordinator::getInstance()->GetComponent<ScrollableComponent>(getId()).offset;
        auto entities = SystemCoordinator::getInstance()->GetComponent<ContentComponent>(getId()).entities;

        rootNode = CreateTreeNode();
        SystemCoordinator::getInstance()->GetComponent<TreeNodeComponent>(rootNode).visible = true;
        SystemCoordinator::getInstance()->GetComponent<TreeNodeComponent>(rootNode).expanded = true;
        loadTree(&app->getRoot(),rootNode,position.x+STARTING_OFFSETX,position.y+STARTING_OFFSETY, entities);
        for (auto& p : entities) {
            std::cout << SystemCoordinator::getInstance()->GetComponent<TextComponent>(p).text << std::endl;
        }
        int entitysize = entities.size();
        segmentIndex.resize(entitysize);
        segmentTree.resize(entitysize*4);
        segmentIndex.push_back({0,0,0});
        initSegmentTree(rootNode);
        buildTree(1, entitysize-1, 1);
        updateTree(0,entities);
    }

    void loadTree(SceneNode* sceneNode, EntityID node, int width, int height, std::vector<EntityID>& entities) {
        SystemCoordinator::getInstance()->GetComponent<TextComponent>(node).text = sceneNode->getName();
        SystemCoordinator::getInstance()->GetComponent<PositionComponent>(node).position = glm::vec2(width,height);
        entities.reserve(entities.size() + 1);
        entities.emplace_back(node);
        for (int i=0; i<sceneNode->getChildren().size(); i++) {
            EntityID child = CreateTreeNode(node);

            loadTree(sceneNode->getChildren()[i], child, width+tabWidth, height+rowHeight*(i+1), entities);
            SystemCoordinator::getInstance()->GetComponent<ContentComponent>(node).entities.emplace_back(child);
        }
        for (int i = 0; i<sceneNode->getComponents().size(); i++)
        {
            EntityID child = CreateTreeNode(node, "work in progress", glm::vec2(width+tabWidth,height+rowHeight*(i+1)));
            SystemCoordinator::getInstance()->GetComponent<ContentComponent>(node).entities.emplace_back(child);
            entities.reserve(entities.size() + 1);
            entities.emplace_back(child);
        }
    }

    void updateTree(int idx, std::vector<EntityID>& nodes) {
        if (idx+1 >= nodes.size()) return;
        int cnt = 0;
        //updateTree(1, nodes.size()-1, idx+1, segmentIndex[idx].start, segmentIndex[idx].end, nodes[idx]->expanded ? -segmentTree[idx+1] : segmentTree[idx+1]);
        int sum1 = sum(1,nodes.size()-1, 1, segmentIndex[idx+1].start, segmentIndex[idx+1].end);
        auto& nodeidx = SystemCoordinator::getInstance()->GetComponent<TreeNodeComponent>(nodes[idx]);
        for (int i = idx+1; i<idx+sum1; i++)
        {
            auto& nodei = SystemCoordinator::getInstance()->GetComponent<TreeNodeComponent>(nodes[i]);
            auto& nodeiparent = SystemCoordinator::getInstance()->GetComponent<TreeNodeComponent>(nodei.parent);
            if (nodeidx.expanded)
            {
                if (!nodeiparent.expanded)
                {
                    i+=sum(1,nodes.size()-1,1,segmentIndex[i+1].start, segmentIndex[i+1].end);
                }
                if (nodeiparent.expanded)
                {
                    nodei.visible = nodeiparent.expanded & nodeidx.expanded;
                    //nodes[i]->icon.visible = nodes[i]->parent->expanded & nodes[idx]->expanded;
                    cnt++;
                }
            }
            else
            {
                if (nodei.visible)
                {
                    nodei.visible = false;
                    //nodes[i]->icon.visible = false;
                    cnt++;
                }
            }
        }
        for (int i = idx+sum1; i<nodes.size(); i++)
        {
            auto& nodei = SystemCoordinator::getInstance()->GetComponent<PositionComponent>(nodes[i]);
            nodei.position.y += cnt*rowHeight * (nodeidx.expanded ? 1 : -1);
            //nodes[i]->icon.position.y += cnt*rowHeight * (nodeidx.expanded ? 1 : -1);
        }
        std::cout << "sum: " << sum1 << std::endl;
        std::cout << "cnt: " << cnt << std::endl;
    }

    EntityID CreateTreeNode(EntityID parent = -1, std::string text="", glm::vec2 pos=glm::vec2()) {
        EntityID id = SystemCoordinator::getInstance()->CreateEntity();
        SystemCoordinator::getInstance()->AddComponent(id, TextComponent{std::move(text)});
        SystemCoordinator::getInstance()->AddComponent(id, PositionComponent{pos});
        SystemCoordinator::getInstance()->AddComponent(id, TreeNodeComponent{0,0,0,-1,parent,getId()});
        SystemCoordinator::getInstance()->AddComponent(id, ContentComponent{});
        return id;
    }

    void update() override {
        *offset = 20;
        std::cout << "offset: " << *offset << std::endl;
    }
};

#endif //ECSOBJECTVIEW_H
