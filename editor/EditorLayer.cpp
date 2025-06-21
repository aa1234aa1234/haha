//
// Created by D412 on 2025-06-18.
//

#include "EditorLayer.h"
#include "TabView.h"

#include "Engine.h"

EditorLayer::EditorLayer(Engine* engine) : engine(engine)
{

}

EditorLayer::~EditorLayer()
{
    delete context;
}

void EditorLayer::init()
{
    context = new UIContext();
    context->init(Engine::getScreenWidth(), Engine::getScreenHeight());

    tabView = new TabView();
    sceneView = new SceneView();
    sceneView->addSceneTexture("Scene", engine->getSceneBuffer()->getFrameTexture());
    sceneView->addSceneTexture("Game", engine->getSceneBuffer()->getFrameTexture());
    tabView->setPanelViewComponent(sceneView);

    context->add(tabView);
    context->add(sceneView);
}

void EditorLayer::render()
{
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    context->DrawComponents();
}

void EditorLayer::update()
{

}



