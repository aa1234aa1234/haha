//
// Created by D412 on 2025-06-18.
//

#include "EditorLayer.h"

#include "ECSObjectView.h"
#include "TabView.h"

#include "Engine.h"
#include "Input.h"
#include "KeydownEvent.h"
#include "TextHandler.h"
#include "SystemCoordinator.h"

EditorLayer::EditorLayer(Engine* engine) : engine(engine)
{
    engine->getEventDispatcher()->registerCallback([this](IEvent& event) { this->handleInput(event); });
}

EditorLayer::~EditorLayer()
{
    delete tabView;
    delete sceneView;
    delete objectView;
    UIContext::destroyInstance();
    SystemCoordinator::destroyInstance();
}

void EditorLayer::RegisterComponents()
{
    SystemCoordinator::getInstance()->RegisterComponent<TransformComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<ContentComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<ScrollableComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<TextComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<TreeNodeComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<PositionComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<HoverableComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<DirtyComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<ClickableComponent>();
    SystemCoordinator::getInstance()->RegisterComponent<RenderableIcon>();
    SystemCoordinator::getInstance()->RegisterComponent<ParentComponent>();
}

void EditorLayer::init()
{
    RegisterComponents();
    TextHandler::makeInstance(Engine::getScreenWidth(), Engine::getScreenHeight(), "resources/font/font (32px).png");
    UIContext::getInstance()->init(Engine::getScreenWidth(), Engine::getScreenHeight(), engine);


    tabView = new TabView(glm::vec2(300,0),glm::vec2(Engine::getScreenWidth()-300,25));
    sceneView = new SceneView();
    //objectView = new ObjectView(glm::vec2(0,0),glm::vec2(200,Engine::getScreenHeight()-200));
    //objectView->init(&engine->getApplication()->getRoot());
    sceneView->addSceneTexture("Scene", engine->getSceneBuffer()->getFrameTexture());
    sceneView->addSceneTexture("Game", engine->getSceneBuffer()->getFrameTexture());
    tabView->setPanelViewComponent(sceneView);

    UIContext::getInstance()->add(tabView);
    UIContext::getInstance()->add(sceneView);
    //UIContext::getInstance()->add(objectView);

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
    UIContext::getInstance()->update();
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
            break;
        case Input::EventType::MOUSE_DRAG:
            UIContext::getInstance()->onDrag(Input::getInstance()->getMousePos(), Input::getInstance()->getMouseDelta());
            break;

    case Input::EventType::KEY_DOWN:
            if (Input::getInstance()->isKeyDown(256)) Engine::setRunning(false);
            break;
    }
}




