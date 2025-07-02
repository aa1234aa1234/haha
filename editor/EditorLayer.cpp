//
// Created by D412 on 2025-06-18.
//

#include "EditorLayer.h"
#include "TabView.h"

#include "Engine.h"
#include "Input.h"

EditorLayer::EditorLayer(Engine* engine) : engine(engine)
{

}

EditorLayer::~EditorLayer()
{
    delete tabView;
    delete sceneView;
}

void EditorLayer::init()
{
    UIContext::getInstance()->init(Engine::getScreenWidth(), Engine::getScreenHeight());

    tabView = new TabView();
    sceneView = new SceneView();
    sceneView->addSceneTexture("Scene", engine->getSceneBuffer()->getFrameTexture());
    sceneView->addSceneTexture("Game", engine->getSceneBuffer()->getFrameTexture());
    tabView->setPanelViewComponent(sceneView);

    UIContext::getInstance()->add(tabView);
    UIContext::getInstance()->add(sceneView);
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

void EditorLayer::handleInput()
{

}




