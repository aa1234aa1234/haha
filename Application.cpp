//
// Created by D412 on 2025-06-16.
//

#include "Application.h"


#include "KeydownEvent.h"
#include "MouseEvent.h"


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputEvent keyEvent = InputEvent(key, action == GLFW_RELEASE ? KeydownEvent::KeyDown::KEY_UP : KeydownEvent::KeyDown::KEY_DOWN);
    inputEvent.push(keyEvent);
}

void Application::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (firstMouse) { lastMousePos = glm::vec2(xpos, ypos); firstMouse = false; }
    InputEvent mouseEvent =InputEvent(glm::vec2(xpos,ypos), action == GLFW_RELEASE ? MouseEvent::MouseEventType::MOUSEUP : MouseEvent::MouseEventType::MOUSEDOWN);
    inputEvent.push(mouseEvent);
    if (action == GLFW_RELEASE) firstMouse = true;
}

void Application::cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{
    int action=0;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != 1) action = 1;
    InputEvent mouseEvent = InputEvent(glm::vec2(xpos,ypos), lastMousePos, action ? MouseEvent::MouseEventType::MOUSEMOVE : MouseEvent::MouseEventType::MOUSEDRAG);
    inputEvent.push(mouseEvent);
    lastMousePos = glm::vec2(xpos,ypos);
}

Application::Application() : root("rootNode")
{
    SceneNode* node = new SceneNode("TestNode1");
    SceneNode* node1 = new SceneNode("TestNode2");
    SceneNode* node2 = new SceneNode("TestNode3");
    SceneNode* node3 = new SceneNode("TestNode4");
    root.addSceneNode(node);
    root.addSceneNode(node1);
    root.addSceneNode(node2);
    node2->addSceneNode(node3);
}

Application::~Application()
{

}

void Application::setCallBack(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window,keyCallback);
    glfwSetMouseButtonCallback(window,mouseCallback);
    glfwSetCursorPosCallback(window,cursorCallback);
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


