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
    glfwSwapInterval(0);
    eventDispatcher = new EventDispatcher();
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
    int fps = TextHandler::getInstance()->addText(10, 10, "");
    float frames = 0;
    char buf[1024];
    while (isRunning)
    {
        frameLimiter.begin();
        float currentFrame = glfwGetTime();
        deltatime = currentFrame - lastframe;
        lastframe = currentFrame;

        sprintf(buf, "FPS: %.1f", frames);
        TextHandler::getInstance()->editText(1000, 860, buf, fps, 1.0);

        glfwPollEvents();

        glDisable(GL_DEPTH_TEST);
        glClearColor(0.09, 0.09, 0.09, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //normal engine code holy shit im making comments omg
        InputEvent event;
        application->pollInputEvent(event);
        handleInput(deltatime,event);
        application->handleInput(deltatime);
        if (editorMode)
        {
            editorLayer->update();
        }
        application->update(deltatime);
        render(deltatime);
        frames = frameLimiter.end();
        //Input::getInstance()->setEventType(-1);
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

void Engine::handleInput(float deltatime, InputEvent& event)
{
    switch (event.getEventType())
    {
    case Input::EventType::MOUSE_DOWN:
        {
            Input::getInstance()->setEventType(Input::EventType::MOUSE_DOWN);
            Input::getInstance()->setMousePos(event.getMousePos());
            MouseEvent mouseEvent = MouseEvent(event.getMousePos(), event.getMouseDelta(), MouseEvent::MouseEventType::MOUSEDOWN);
            eventDispatcher->dispatchEvent(mouseEvent);
        }
        break;
    case Input::EventType::MOUSE_UP:
        {
            MouseEvent mouseEvent = MouseEvent(event.getMousePos(), MouseEvent::MouseEventType::MOUSEUP);
            eventDispatcher->dispatchEvent(mouseEvent);
            Input::getInstance()->setEventType(Input::EventType::MOUSE_UP);
            Input::getInstance()->setMousePos(event.getMousePos());
        }
        break;
    case Input::EventType::MOUSE_MOVE:
        {
            MouseEvent mouseEvent = MouseEvent(event.getMousePos(), event.getMouseDelta(), MouseEvent::MouseEventType::MOUSEMOVE);
            eventDispatcher->dispatchEvent(mouseEvent);
            Input::getInstance()->setEventType(Input::EventType::MOUSE_MOVE);
            Input::getInstance()->setMousePos(event.getMousePos());
            Input::getInstance()->setMouseDelta(event.getMouseDelta());
        }

        break;
    case Input::EventType::MOUSE_DRAG:
        {
            MouseEvent mouseEvent = MouseEvent(event.getMousePos(), event.getMouseDelta(), MouseEvent::MouseEventType::MOUSEDRAG);
            eventDispatcher->dispatchEvent(mouseEvent);
            Input::getInstance()->setEventType(Input::EventType::MOUSE_DRAG);
            Input::getInstance()->setMousePos(event.getMousePos());
            Input::getInstance()->setMouseDelta(event.getMouseDelta());
        }
        break;
    case Input::EventType::KEY_DOWN:
        {
            Input::getInstance()->setEventType(Input::EventType::KEY_DOWN);
            Input::getInstance()->setKeyDown(event.getKey(), true);
            KeydownEvent keydown = KeydownEvent(event.getKey(),Input::EventType::KEY_DOWN);
            eventDispatcher->dispatchEvent(keydown);
        }
        break;
    case Input::EventType::KEY_UP:
        {
            Input::getInstance()->setEventType(Input::EventType::KEY_UP);
            Input::getInstance()->setKeyDown(event.getKey(), false);
            KeydownEvent keydown = KeydownEvent(event.getKey(),Input::EventType::KEY_UP);
            eventDispatcher->dispatchEvent(keydown);
        }
        break;
    }
    if (application->getInputEvents().size()) application->getInputEvents().pop();
}
