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
}

void Application::cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{
    int action=0;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != 1) action = 1;
    MouseEvent* mouseEvent = new MouseEvent(glm::vec2(xpos,ypos), lastMousePos, action ? MouseEvent::MOUSEDRAG : MouseEvent::MOUSEMOVE);
    inputEvent.push(mouseEvent);
    lastMousePos = glm::vec2(xpos,ypos);
}

Application::Application()
{

}

Application::~Application()
{

}

void Application::setCallBack(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window,keyCallback);
    glfwSetMouseButtonCallback(window,mouseCallback);
}

void Application::render()
{

}

void Application::handleInput(float deltatime)
{
    root.handleInput();
}

void Application::update(float deltatime)
{
    root.update(deltatime);
}


