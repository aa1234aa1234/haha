//
// Created by D412 on 2025-06-16.
//

#include "Application.h"


#include "KeydownEvent.h"
#include "MouseEvent.h"
#include "ScrollEvent.h"
#include "rendering/RenderingEngine.h"
#include "Input.h"


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputEvent keyEvent = InputEvent(key, action == GLFW_RELEASE ? KeydownEvent::KeyDown::KEY_UP : KeydownEvent::KeyDown::KEY_DOWN);
    inputEvent[keyEvent.getEventType()].push(keyEvent);
}

void Application::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (firstMouse) { lastMousePos = glm::vec2(xpos, ypos); firstMouse = false; }
    InputEvent mouseEvent =InputEvent(glm::vec2(xpos,ypos), action == GLFW_RELEASE ? MouseEvent::MouseEventType::MOUSEUP : MouseEvent::MouseEventType::MOUSEDOWN);
    inputEvent[mouseEvent.getEventType()].push(mouseEvent);
    if (action == GLFW_RELEASE) firstMouse = true;
}

void Application::cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{
    int action=0;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != 1) action = 1;
    InputEvent mouseEvent = InputEvent(glm::vec2(xpos,ypos), lastMousePos-glm::vec2(xpos,ypos), action ? MouseEvent::MouseEventType::MOUSEMOVE : MouseEvent::MouseEventType::MOUSEDRAG);
    inputCnt[mouseEvent.getEventType()]++;
    inputEvent[mouseEvent.getEventType()].push(mouseEvent);
    lastMousePos = glm::vec2(xpos,ypos);
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    InputEvent scrollEvent = InputEvent(xoffset,yoffset, ScrollEvent::ScrollEventType::SCROLL);
    inputEvent[scrollEvent.getEventType()].push(scrollEvent);
}

void Application::error_callback(void* user_data, int error, const char* description) {
    std::cerr << error << ' ' << description << '\n';
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
    for (int i = 0; i<10; i++) {
        node3->addSceneNode(new SceneNode("TestNode" + std::to_string(i+5)));
    }
    for (int i = 15; i<100; i++)
    {
        root.addSceneNode(new SceneNode("TestNode" + std::to_string(i)));
    }
    for (int i = 0; i<30; i++) {
        root.getChildren()[2]->getChildren()[0]->getChildren()[6]->addSceneNode(new SceneNode("TestNode1000000000000000000000"));
        root.getChildren()[2]->getChildren()[0]->getChildren()[6]->addSceneNode(new SceneNode("TestNode"));
        root.getChildren()[2]->getChildren()[0]->getChildren()[6]->addSceneNode(new SceneNode("TestNode"));
    }

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
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetErrorCallback(globalErrorHandler);
    ErrorHandler errorHandler = error_handler;
    errorHandler.user_data = this;
    errorHandler.handler = [](void* user_data, int error, const char* description) {
        std::cout << error << ' ' << description << '\n';
    };
    glfwRequestWindowAttention(window);
    error_handler = errorHandler;
}

void Application::render(RenderingEngine* renderingengine)
{
    glClearColor(0.0, 1.0, 1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderingengine->render(&root);
}

void Application::handleInput(float deltatime)
{
    root.handleInput();
}

void Application::update(float deltatime)
{
    root.update(deltatime);
}

void Application::popEvent() {
    for (int i = 0; i<inputEvent.size(); i++) {
        if (inputEvent[i].size()) inputEvent[i].pop();
    }
}



