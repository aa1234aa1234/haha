//
// Created by D412 on 2025-06-18.
//
#pragma once

#ifndef EDITORLAYER_H
#define EDITORLAYER_H
#include "UIContext.h"
#include "SceneView.h"

class Engine;
class TabView;

class EditorLayer {
    Engine* engine = nullptr;

    UIContext* context=nullptr;
    TabView* tabView=nullptr;
    SceneView* sceneView=nullptr;
public:
    EditorLayer(Engine* engine);
    ~EditorLayer();

    void init();
    void render();
    void update();
    void handleInput();
};



#endif //EDITORLAYER_H
