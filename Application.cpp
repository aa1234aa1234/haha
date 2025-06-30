//
// Created by D412 on 2025-06-16.
//

#include "Application.h"

#include "Input.h"
#include "KeydownEvent.h"
#include "MouseEvent.h"


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    KeydownEvent* keyEvent = new KeydownEvent(key);
    inputEvent.push(keyEvent);
}

void Application::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    MouseEvent* mouseEvent = new MouseEvent(glm::vec2(xpos,ypos), lastMousePos, action == GLFW_RELEASE ? MouseEvent::MOUSEUP : MouseEvent::MOUSEDOWN);
    inputEvent.push(mouseEvent);
    lastMousePos = glm::vec2(xpos,ypos);
}

Application::Application()
{

}

Application::~Application()
{

}

void Application::render()
{

}

void Application::handleInput()
{
    root.handleInput();
}

void Application::update()
{
    root.update();
}


