//
// Created by D412 on 2025-06-18.
//

#include "EditorLayer.h"

#include "ECSAssetBrowser.h"
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
    //delete tabView;
    //delete sceneView;
    //delete objectView;
    UIContext::destroyInstance();
    SystemCoordinator::destroyInstance();
}

void EditorLayer::RegisterComponents()
{
    auto* sc = SystemCoordinator::getInstance();
    sc->RegisterComponent<TransformComponent>();
    sc->RegisterComponent<ContentComponent>();
    sc->RegisterComponent<ScrollableComponent>();
    sc->RegisterComponent<TextComponent>();
    sc->RegisterComponent<TreeNodeComponent>();
    sc->RegisterComponent<PositionComponent>();
    sc->RegisterComponent<HoverableComponent>();
    sc->RegisterComponent<DirtyComponent>();
    sc->RegisterComponent<ClickableComponent>();
    sc->RegisterComponent<RenderableIcon>();
    sc->RegisterComponent<ParentComponent>();
    sc->RegisterComponent<TextureComponent>();
    sc->RegisterComponent<NonRenderableBoundingBox>();
    sc->RegisterComponent<HandleInput>();
    sc->RegisterComponent<RenderableIcons>();
    sc->RegisterComponent<Container>();
    sc->RegisterComponent<TitleComponent>();
    sc->RegisterComponent<LogComponent>();
    sc->RegisterComponent<HoverHightlightComponent>();
}

void EditorLayer::init()
{
    RegisterComponents();
    TextHandler::makeInstance(Engine::getScreenWidth(), Engine::getScreenHeight(), "resources/font/font (32px).png");
    UIContext::getInstance()->init(Engine::getScreenWidth(), Engine::getScreenHeight(), engine);


    //tabView = new TabView(glm::vec2(300,0),glm::vec2(Engine::getScreenWidth()-300,25));
    //sceneView = new SceneView();
    //objectView = new ObjectView(glm::vec2(0,0),glm::vec2(200,Engine::getScreenHeight()-200));
    //objectView->init(&engine->getApplication()->getRoot());
    //sceneView->addSceneTexture("Scene", engine->getSceneBuffer()->getFrameTexture());
    //sceneView->addSceneTexture("Game", engine->getSceneBuffer()->getFrameTexture());
    //tabView->setPanelViewComponent(sceneView);

    //UIContext::getInstance()->add(tabView);
    //UIContext::getInstance()->add(sceneView);
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
            if (Input::getInstance()->isKeyDown(GLFW_KEY_LEFT_ALT) && Input::getInstance()->isKeyDown(GLFW_KEY_F4)) Engine::setRunning(false);
            break;
    }
}




