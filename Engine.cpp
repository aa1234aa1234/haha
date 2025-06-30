//
// Created by user on 6/15/2025.
//

#include "Engine.h"

#include "Input.h"
#include "KeydownEvent.h"
#include "MouseEvent.h"

int Engine::screenHeight, Engine::screenWidth;
bool Engine::isRunning = false;
bool Engine::editorMode = false;

Engine::Engine(Application* app, int& width, int& height, const std::string& title) : window(), uiLayer(new UILayer(this)), editorLayer(new EditorLayer(this)) {
    screenWidth = width;
    screenHeight = height;
    window.init(width,height,title);
    uiLayer->init(window);
    editorLayer->init();
    sceneBuffer = new FrameBuffer(screenWidth,screenHeight);
}

Engine::~Engine()
{
    delete application;
    delete uiLayer, delete editorLayer;
    delete sceneBuffer;
}

void Engine::run()
{
    double deltatime = 0.0, lastframe = 0.0;
    bool firstmouse = true;

    while (isRunning)
    {
        float currentFrame = glfwGetTime();
        deltatime = currentFrame - lastframe;
        lastframe = currentFrame;
        glfwPollEvents();

        //normal engine code holy shit im making comments omg
        handleInput();
        if (!editorMode)
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
}

void Engine::handleInput()
{
    IEvent* event = application->getLastInput();
    if (event->getId() == "MouseEvent")
        Input::getInstance()->setMousePos(event->getAs<MouseEvent*>()->getMousePos());
    else if (event->getId() == "KeyDownEvent")
        Input::getInstance()->setKeyDown(event->getAs<KeydownEvent*>()->getKeycode());
    delete event;
    application->handleInput();
}
