//
// Created by D412 on 2025-06-18.
//

#include "EditorLayer.h"
#include "TabView.h"

#include "Engine.h"
#include "Input.h"
#include "KeydownEvent.h"
#include "TextHandler.h"

EditorLayer::EditorLayer(Engine* engine) : engine(engine)
{
    engine->getEventDispatcher()->registerCallback([this](IEvent& event) { this->handleInput(event); });
}

EditorLayer::~EditorLayer()
{
    delete tabView;
    delete sceneView;
    UIContext::destroyInstance();
}

void EditorLayer::init()
{
    UIContext::getInstance()->init(Engine::getScreenWidth(), Engine::getScreenHeight());
    TextHandler::makeInstance(Engine::getScreenWidth(), Engine::getScreenHeight(), "resources/font/font (32px).png");

    tabView = new TabView(glm::vec2(0,0),glm::vec2(Engine::getScreenWidth(),25));
    sceneView = new SceneView();
    sceneView->addSceneTexture("Scene", engine->getSceneBuffer()->getFrameTexture());
    sceneView->addSceneTexture("Game", engine->getSceneBuffer()->getFrameTexture());
    tabView->setPanelViewComponent(sceneView);

    UIContext::getInstance()->add(tabView);

    UIContext::getInstance()->setup();
}

void EditorLayer::render()
{
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    UIContext::getInstance()->DrawComponents(*engine);
}

void EditorLayer::update()
{
    //i will come back to this at a later date
    //UIContext::getInstance()->dispatchUpdate();
}

void EditorLayer::handleInput(IEvent& event)
{
    if (!Engine::getMode()) return;
    switch (event.getId())
    {
        case Input::EventType::MOUSE_DOWN:
            UIContext::getInstance()->onClick(Input::getInstance()->getMousePos());
            break;
        case Input::EventType::MOUSE_UP:
            UIContext::getInstance()->onRelease(Input::getInstance()->getMousePos());
            break;
        case Input::EventType::MOUSE_MOVE:
            std::cout << "mousemove" << std::endl;
            break;
        case Input::EventType::MOUSE_DRAG:
            UIContext::getInstance()->onDrag(Input::getInstance()->getMousePos(), Input::getInstance()->getMouseDelta());
            break;

        case Input::EventType::KEY_DOWN:

            if (Input::getInstance()->isKeyDown(256)) Engine::setRunning(false);
            break;
    }
}




