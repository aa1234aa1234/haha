//
// Created by D412 on 2025-06-16.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Window.h"
#include "SceneNode.h"

#include "EventDispatcher.h"
#include "Input.h"
#include "InputEvent.h"


class Application {

    SceneNode root;
    std::queue<InputEvent> inputEvent;
    glm::vec2 lastMousePos;
    bool firstMouse = true;
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->key_callback(window, key, scancode, action, mods);
    }
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) app->mouse_callback(window, button, action, mods);
    }
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
        Application *app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) { app->cursorpos_callback(window, xpos, ypos); }
    }
public:
    Application();
    ~Application();

    std::queue<InputEvent>& getInputEvents() { return inputEvent; }
    void pollInputEvent(InputEvent& event)
    {
        if (inputEvent.size())
        {
            event = inputEvent.front();
        }
    }

    void render();
    void update(float deltatime);
    void handleInput(float deltatime);

    void setCallBack(GLFWwindow* window);
};





#endif //APPLICATION_H
