//
// Created by D412 on 2025-06-18.
//

#include "EditorLayer.h"

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
    //tabView->setViewComponent<SceneView>(sceneView);

    context->add(tabView);
    context->add(sceneView);
}

void EditorLayer::render()
{
    context->DrawComponents();
}


