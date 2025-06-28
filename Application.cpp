//
// Created by D412 on 2025-06-16.
//

#include "Application.h"

#include "Input.h"


Application::Application()
{

}

Application::~Application()
{

}

void Application::handleInput()
{
    switch (Input::getInstance()->getEventType())
    {
    case Input::MOUSE_DOWN:
    case Input::MOUSE_UP:
        root->handleInput(Input::getInstance()->getMousePos());
        break;
    case Input::KEY_DOWN:
        root->handleInput(Input::getInstance()->getKeyDown());
        break;
    }
}

void Application::run()
{

}


