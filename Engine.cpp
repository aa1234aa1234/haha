//
// Created by user on 6/15/2025.
//

#include "Engine.h"

#include "Input.h"
#include "KeydownEvent.h"
#include "MouseEvent.h"
#include "TextHandler.h"

int Engine::screenHeight, Engine::screenWidth;
bool Engine::isRunning = false;
bool Engine::editorMode = false;

Engine::Engine(Application* app, const int& width, const int& height, const std::string& title) : window(), application(app) {
    screenWidth = width;
    screenHeight = height;
    window.init(width,height,title);
    application->setCallBack(window.getWindow());
    sceneBuffer = new FrameBuffer(screenWidth,screenHeight);
    uiLayer = new UILayer(this);
    editorLayer = new EditorLayer(this);
    uiLayer->init(window);
    editorLayer->init();
}

Engine::~Engine()
{
    delete application;
    delete uiLayer, delete editorLayer;
    delete sceneBuffer;
}

void Engine::run()
{
    float deltatime = 0.0, lastframe = 0.0;
    bool firstmouse = true;

    while (isRunning)
    {
        float currentFrame = glfwGetTime();
        deltatime = currentFrame - lastframe;
        lastframe = currentFrame;
        glfwPollEvents();

        glDisable(GL_DEPTH_TEST);
        glClearColor(0.09, 0.09, 0.09, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //normal engine code holy shit im making comments omg
        handleInput(deltatime);
        if (editorMode)
        {
            editorLayer->handleInput();
            editorLayer->update();
        }
        render(deltatime);
        //ill leave this here need to making editor layer
        window.swapBuffers();
    }

}

void Engine::render(float deltatime)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sceneBuffer->bind();
    application->render();

    if (editorMode)
    {
        sceneBuffer->unbind();
    }

    uiLayer->render();
    if (editorMode)
    {
        editorLayer->render();
    }
    TextHandler::getInstance()->draw();
}

void Engine::handleInput(float deltatime)
{
    IEvent* event = application->getLastInput();
    if (event == nullptr) return;
    if (event->getId() == "MouseEvent")
    {
        Input::getInstance()->setMousePos(event->getAs<MouseEvent*>()->getMousePos());
        Input::getInstance()->setEventType(event->getAs<MouseEvent*>()->getEventType());
    }
    else if (event->getId() == "KeyDownEvent")
    {
        Input::getInstance()->setKeyDown(event->getAs<KeydownEvent*>()->getKeycode());
        Input::getInstance()->setKeyDown(event->getAs<KeydownEvent*>()->getEventType());
    }
    delete event;
    application->handleInput(deltatime);
}
